
// t is time in seconds = millis()/1000;
char * TimeToString(unsigned long t)
{
  static char str[12];
//  t = currentMillis/1000;
  long h = t / 3600;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;
  sprintf(str, "%04ld:%02d:%02d", h, m, s);
  return str;
} 


