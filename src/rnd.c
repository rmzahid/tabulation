int round(float x)
{
  int y;
  y=(int)x;
  if ((x-y)<0.5)
	return y;
  else
	return y+1;
}
