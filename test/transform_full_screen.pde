void setup() {
  fullScreen();
  background(#000000);
  stroke(#00FF00);
  noFill();
  noSmooth();
  int u,v;
  float x,y;
  
  String[] lines = loadStrings("c:/rodolfoap/transform_full_screen.test.dat");
  float screenfactor=0.4;
  float transfactor=200000;
  float offsetx=200;
  float offsety=100;
  for (int i = 0 ; i < lines.length; i++) {
    float[] nums = float(split(lines[i], ','));
    u=int(nums[0]*screenfactor); 
    v=int(nums[1]*screenfactor);
    x=(-nums[2]+43.6096)*transfactor+offsetx;
    y=(-nums[3]+6.951)*transfactor+offsety;
    println(u, v, x, y," ;", lines[i], ";");
    
    stroke(#00FF00);    // green
    if(nums[0]==0){stroke(#FF0000);}//Red
    if(nums[0]==640){stroke(#0000FF);}//blue
    if(nums[1]==0){stroke(#FF00FF);}//magenta
    if(nums[1]==420){stroke(#FFFF00);}//yellow
    point(u, v);
    point(x, y);
  }
  println("Total: " + lines.length + " lines.");
  save("c:/rodolfoap/transform_full_screen.test.png");
}
