/**************************
 *                        * 
 *     File Sim           * 
 *                        *
 * By: Michael Wang       *
 *                        *
 *                        *
 *Description: Displays   *
 *  the p_pos and r_pos   *
 *  files in Open GL      *
 *                        *
 * in: p_pos, r_pos       *
 *                        * 
 * out: OpenGL vid        *
 *                        *
 **************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "strtoint.c"

char **command_args;
int command_nums;
int frames,xsize,ysize,r_tot,p_tot, type, shiftx, shifty, delay;
int pausesec;
int sizex,sizey, numskip;
float R_SIZE,P_SIZE;
int i, j, k, l; // delay variables

void display(void) {
  int ii,i, k, curframe=0, flag,kk=0, clust;
  float rx, ry, px, py, homex, homey;
  char a[100],b[100],c[100], inchain, str[100], exist;
  FILE *r_pos;
  FILE *p_pos;
  FILE *settings;

  // reads from the file r_pos.dat and p_pos.dat, set the directory to files 
  command_args++;
  settings=fopen(*++command_args,"r");
  r_pos = fopen(*++command_args, "r");
  p_pos = fopen(*++command_args, "r");

  if ((r_pos==NULL)||(p_pos==NULL)||(settings==NULL)) {
     printf("One of the files couldn't be opened!  Exiting.\n");
     exit(-1);
  }

  fscanf(settings,"%d\n",&frames);
  fscanf(settings,"%d\n",&xsize);
  fscanf(settings,"%d\n",&ysize);
  fscanf(settings,"%d\n",&r_tot);
  fscanf(settings,"%f\n",&R_SIZE);
  fscanf(settings,"%d\n",&p_tot);
  fscanf(settings,"%f\n",&P_SIZE);

  fscanf(r_pos, "%s", &str); // get home location
  fscanf(r_pos, "%s", str);
  sscanf(str, "%f", &homex);
  fscanf(r_pos, "%s", str);
  sscanf(str, "%f", &homey);
  fclose(settings);

  printf("Home: (%.2f, %.2f)\n", homex, homey);
  printf("Frames: %d\n",frames);
  printf("X-Size: %d\n",xsize);
  printf("Y-Size: %d\n",ysize);
  printf("Number of robots: %d\n",r_tot);
  printf("Size of robots: %.3f\n",R_SIZE);
  printf("Number of pucks: %d\n",p_tot);
  printf("Size of pucks: %.3f\n",P_SIZE);
  
  do {
    for(kk=0; kk<numskip; kk++) {
      for(ii=0; ii<r_tot; ii++) {
	flag=fscanf(r_pos, "%s %s %s", str, str, str);
	if(flag!=3) {
	  sleep(5);
	  exit(1);
	}
      }
    }
    for(kk=0; kk<numskip; kk++) {
      for(ii=0; ii<p_tot; ii++) {
	flag=fscanf(p_pos, "%s %s %s %s", str, str, str, str);
	if(flag!=4) {
	  sleep(5);
	  exit(1);
	}
      }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    
    // display home location
    glColor3f(.85, .85, .85);
    glTranslatef(homex + shiftx, homey + shifty, 0.0);
    glutSolidSphere(R_SIZE+6, 10.0, 10.0);
    glTranslatef(-homex - shiftx, -homey - shifty, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(homex + shiftx, homey + shifty, 0.0);
    glutSolidSphere(R_SIZE+5.5, 10.0, 10.0);
    glTranslatef(-homex - shiftx, -homey - shifty, 0.0);
    
    // display robots
    for(i=0; i<r_tot; i++){

      if(fscanf(r_pos, "%s", str)!=1) {
        sleep(5);
        exit(1);
      }
      sscanf(str, "%c", &inchain);

      fscanf(r_pos, "%s", str);
      sscanf(str, "%f", &rx);

      fscanf(r_pos, "%s", str);
      sscanf(str, "%f", &ry);

      if(inchain=='c')
        glColor3f(0.0, 0.0, 1.0);
      if(inchain=='n')
        glColor3f(1.0, 0.0, 0.0);
      if(inchain=='d')
        glColor3f(0.643137255, 0.329411765, 0.117647059);      

      glTranslatef(rx+shiftx, ry+shifty, 0.0);
      glutSolidSphere(R_SIZE, 10.0, 10.0);
      glTranslatef(-rx-shiftx, -ry-shifty, 0.0);
    }

    // display pucks
    for(k=0; k<p_tot; k++) {
      if(fscanf(p_pos, "%s", str)!=1) {
        sleep(5);
        exit(1);
      }
      sscanf(str, "%c", &exist);
      
      fscanf(p_pos, "%s", str);
      sscanf(str, "%f", &px);
      
      fscanf(p_pos, "%s", str);
      sscanf(str, "%f", &py);
      
      fscanf(p_pos, "%s", str);
      sscanf(str, "%d", &clust);

      if(exist=='e')
        glColor3f(0.0, 0.0, 0.0);
      if(exist=='d')
        glColor3f(0.0, 0.5, 0.0);
      
      glTranslatef(px+shiftx, py+shifty, 0.0);
      glutSolidSphere(P_SIZE, 10.0, 10.0);
      glTranslatef(-px-shiftx, -py-shifty, 0.0);
    }
    
    if(rx!= EOF) {
      glutSwapBuffers();
    }
    curframe++;
    sleep(pausesec);
    for(i = 0; i < delay; i++) {
      for(j = 0; j < delay; j++) {
        for(k = 0; k < delay; k++) {
          for(l = 0; l < delay; l++) {
          }
        }
      }
    }
  } while (curframe<frames);
  
  fclose(r_pos);
  fclose(p_pos);
  sleep(3);
  exit(1);
}

void init(void) {
  
  glClearColor(1.0, 1.0, 1.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, sizex, 0.0, sizey, -10.0, 10.0);
}

int main(int argc, char *argv[]) {
  if((argc<5)||(argc>11)) {
    printf("Incorrect format:  rfile_sim <delay int> <settings file>\n"); 
    printf("<robot file name> <puck file name> [shiftx] [shifty] [sizex]\n");
    printf("[sizey] [num_skipped] [seconds pause per frame]\n");
    exit(-1);
  }
  if(argc>=6)
    sscanf(argv[5],"%d ",&shiftx);
  else
    shiftx=0; 
  if(argc>=7)
    sscanf(argv[6],"%d ",&shifty);
  else
    shifty=0;
  if(argc>=8)
    sscanf(argv[7],"%d ",&sizex);
  else
    sizex=0;
  if(argc>=9)
    sscanf(argv[8],"%d ",&sizey);
  else
    sizey=0;
  if(argc>=10)
    sscanf(argv[9],"%d ",&numskip);
  else
    numskip=0;
  if(argc>=11)
    sscanf(argv[10],"%d ",&pausesec);
  else
    pausesec=0;

  delay = strtoint(argv[1]);

  printf("Sizex - %d Sizey - %d Shiftx - %d Shifty - %d Skip - %d\n",sizex,sizey,shiftx,shifty,numskip);
  command_nums=argc;
  command_args=argv;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(770, 770);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Create!");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
} 
