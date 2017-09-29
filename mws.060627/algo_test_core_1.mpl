distancia := proc( i )
  local r, s, t; global p4;

  r := (c_a*clave)/(clave-i*c_a);
  s := -(r - raiz);
  t := ((s*clave)-(c_a*clave))/(c_a*s);
  s := (c_a*clave)/(clave-t*c_a);
  p4 := round(t);

  point(P1,[i,r]):
  point(P2,[t,s]):

  return distance(P1,P2);

end proc:
lower := proc( left, right )
  local l, m_1, m, m1, r, new_left, middle, new_right, diff, divisor;

  new_left := left;
  new_right:= right;
  diff := new_right - new_left;
  divisor := div;

  if( diff < 4 ) then
    new_right := right + (4-diff);
    diff := new_right - new_left;
  end if;

  middle := ceil( new_left+((new_right-new_left)/2) );

  l  := distancia( new_left );
  m_1:= distancia( middle-1 );
  m  := distancia( middle );
  m1 := distancia( middle+1 );
  r  := distancia( new_right );

  if( diff = 4 ) then
    if( l < m_1 ) then 
      return [new_left,l]; 
    elif( m_1 < m ) then
      return [middle-1,m_1];
    elif( m < m1 ) then
      return [middle,m];
    elif( m1 < r ) then
      return [middle+1,m1]
    else
      return [new_right,r];
    end if;
  elif( (l < m_1) or (m_1 < m) ) then
    new_right:= middle-1;
    return lower( new_left, new_right );
  elif( (m_1 > m) and (m < m1) ) then
    return [middle,m];
  elif( (m > m1) and ( (m1 < r) or ( r < m1) ) ) then
    new_left := middle+1;
    return lower( new_left, new_right );
  end if;

end proc:# 
higher := proc( i )
  local p1, p2, p3;
  p1 := distancia( i-1 );
  p2 := distancia( i );
  p3 := distancia( i+1 );
  if( (p1 > p2) and (p1 > p3) ) then
    return [i-1,p1];
  elif( (p2 > p1) and (p2 > p3) ) then
    return [i,p2];
  else return [i+1,p3];
  end if;
end proc:
ask_one := proc( low, up, div )
  local res, l, u;

  l := distancia( low );
  u := distancia( up );

  if( l < u ) then
    res := evalf(u/l);
  else
    res := evalf(l/u);
  end if;

  return res;

end proc:
tanto13 := proc( p1, p2, p3 )
  local d1, d2, t, i, low_below, low_over, div, low_div, over_div, top, temp, LT1, LT2, TopPointT2;
  global clave, raiz, a, c_a;
  Digits:=250;
  with(geometry);
  _EnvHorizontalName := x;
  _EnvVerticalName := y;

  clave := p1 * p2;
  raiz := evalf(sqrt(clave));

  a  := evalf( clave / ( clave - raiz ) );
  c_a:= a * raiz;

  # Original Triangle T1

  low_below := [p1-1,distancia( p1-1 )];
  top       := higher( trunc( raiz ) );
  low_over  := [p2-1,distancia( p2-1 )];

  point( PT1, low_below );
  point( PT2, top );
  point( PT3, low_over );

  triangle( T1, [PT1,PT2,PT3] );

  centroid( C1, T1 );
  orthocenter( O1, T1 );

  incircle( inc1, T1, 'centername'=i1 );
  
  circumcircle( circ1, T1, 'centername'=c1 );
  
  point(inc1center,coordinates( center( inc1 ) ) );
  point(circ1center,coordinates( center( circ1 ) ) );

  line(LineT11,[PT1,PT2]);
  line(LineT12,[PT3,PT2]);
  line(CENTRES1,[C1,O1]);

  # Guess Triangle T2

  low_below := [p3-1,distancia( p3-1 )];
  div       := p4;
  top       := higher( trunc(raiz) );
  low_over  := [div,distancia( div )];

  if( low_below[2] > low_over[2] ) then
    temp := low_below[2];
    low_below[2] := low_over[2];
    low_over[2] := temp;
  end if;

  point( PT4, low_below );
  point( PT5, top );
  point( PT6, low_over );
  triangle( T2, [PT4,PT5,PT6] );

  centroid( C2, T2 );
  orthocenter( O2, T2 );

  incircle( inc2, T2,'centername'=i2 );
  

  circumcircle( circ2, T2, 'centername'=c2 );
  TopPointT2 := coordinates(center(circ2));
  TopPointT2[2] := TopPointT2[2]+radius(circ2);
  

  point(inc2center,coordinates( center( inc2 ) ) );
  point(circ2center,coordinates( center( circ2 ) ) );

  line(LineT21,[PT4,PT5]);
  line(LineT22,[PT5,PT6]);
  line(CENTRES2,[C2,O2]);

  line(THL,y=VerticalCoord(PT5),[x,y]);
#  line(THL,y=TopPointT2[2],[x,y]);

  TangentLine(TLine2,PT2,circ2,[TLine21,TLine22]);
#  tangentpc(TLine21,PT5,circ2);
  

  # Rotation of T2

#  rotation(T3,T2,slope(TLine21),'clockwise',PT5);
  rotation(T3,T2,FindAngle(THL,TLine21),'clockwise',PT5);
  centroid( C3, T3 );
  orthocenter( O3, T3 );

  incircle( inc3, T3,'centername'=i3 );
  

  circumcircle( circ3, T3, 'centername'=c3 );
  

  point(inc3center,coordinates( center( inc3 ) ) );
  point(circ3center,coordinates( center( circ3 ) ) );
  
  line(CENTRES3,[C3,O3]); 

  

  # Output prints and plot
  Digits:= 50;

  # Input parameters
  print(p1,p2,clave,raiz);

  # T1 Details (Primes triangle, not known!)
  print( "T1 Details:" );
  print( "incircle center", coordinates(center(inc1)) );
  print( "incircle radius", radius(inc1) );
  print( "circumcircle center", coordinates(center(circ1)) );
  print( "circumcircle radius", radius(circ1) );
  print( low_below );
  print( top );
  print( low_over );
  print( abs( low_below[2]-low_over[2] ) );
  print( area( T1 ) );
  print( coordinates( C1 ) );
  print( coordinates( O1 ) );

  printf("\n");

  # T2 Details
  print( "T2 Details:" );
  print( "incircle center", coordinates(center(inc2)) );
  print( "incircle radius", radius(inc2) );
  print( "circumcircle center", coordinates(center(circ2)) );
  print( "circumcircle radius", radius(circ2) );
  print( p3-1, div );
  print( low_below );
  print( top );
  print( low_over );
  print( abs( low_below[2]-low_over[2] ) );
  print( area( T2 ) );
  print( coordinates( C2 ) );
  print( coordinates( O2 ) );
  print( "coordinates of T2" );
  print( "slopes", slope(LineT21), slope(LineT22) );
  print( slope(TLine21) );
  print( FindAngle( THL,TLine21 ) );

  printf("\n");

  # T3 Details
  print( "T3 Details:" );
  print( "incircle center", coordinates(center(inc3)) );
  print( "incircle radius", radius(inc3) );
  print( "circumcircle center", coordinates(center(circ3)) );
  print( "circumcircle radius", radius(circ3) );

  print("\n");

  print( "CENTRES, y=0" );
  print( solve({Equation(CENTRES1),y=0}) );
  print( solve({Equation(CENTRES2),y=0}) );
  print( solve({Equation(CENTRES3),y=0}) );
  print( "Intersection CENTRES2|CENTRES3" );
  print( solve({Equation(CENTRES2),Equation(CENTRES3)}) );


draw( [THL, T1(colour=green), T2(colour=red), C1(colour=green), C2(colour=red), O1(colour=magenta), O2(colour=black), inc1center(colour=green), circ1center(colour=green), inc2center(colour=red), circ2center(colour=red), TLine21(colour=red), T3(colour=blue), C3(colour=blue), O3(colour=blue), inc3center(colour=blue), circ3center(colour=blue), CENTRES1(colour=green), CENTRES2(colour=red), CENTRES3(colour=blue)], axes=normal, scaling=unconstrained );

end proc:# 

