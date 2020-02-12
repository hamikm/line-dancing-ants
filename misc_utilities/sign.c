float sign(float x)
{
   float data;
   if (x*x<0.0001)
   {
      data=0.0;
      return(data);
   }
   if (x<0)
   {
      data=-1.0;
      return(data);
   }
   data=1.0;
   return(data);
}
