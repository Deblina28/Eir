#define alpha 0.2
#define alpha2 0.1

#define n 200


int data[n];

void setup() {

  pinMode(A0, INPUT_PULLUP);
  Serial.begin(38400);

  for (int i = 0; i < n; i++)
     data[i] = 0;
}

float x, y, raw, sum = 0, avg = 0, braw = 0.0, max = 0, bpm=0.0;
int idx = 0;
int f = 1, ct = 0;
long ls=0, ps=0,cs=0;

void loop() {
  
  

float bpmavg=0;
int zt=0;
for(int i=0;i<11;)
{
  braw = calRaw();
 
  if(braw>2 && f)
  {
    ps=millis()-ls;
    ls=millis();
    f=0;
    i++;
    bpmavg+=bpm;
    bpm= (1000.0/ps)*60;
    ct++;
    
    /*Serial.print(". ");
    Serial.print(" ");
    Serial.println(bpm);*/

  }

  else if(braw<-0.5)
  f=1;

  if(millis()-cs>=60000)
  {
    zt=ct;
    ct=0;
    cs=millis();
  }
    Serial.println(calRaw());
    /*Serial.print(" ");
    Serial.println(bpm);*/
  delay(1);
  }
  
    /*Serial.print(zt*6);
    Serial.print(" ");  
    Serial.println(bpmavg/11);*/
    
  
     
}

  float calRaw()
  {
    raw = analogRead(A0);
    x  = alpha * raw + (1 - alpha) * x;
    y  = alpha2 * x + (1 - alpha2) * y;

    sum -= data[idx];
    data[idx] = raw;
    sum += raw;

    idx = (idx + 1) % n;

    avg = sum / n;

    return (y - avg);
  }
