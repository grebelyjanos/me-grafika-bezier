/*
 * Grafika beadandó 2020 - 2D bezier görbe kirajzolása
 *
 * Írta Grebely János / CL4WWB / - G1BIL
 *
 * A program célja 2D bezier görbe kirajzolása.
 * Maximum pontok száma PMSIZE makróban definiálható.
 *
 * A program alapvető interrakcióra képes a lentebb írtak alapján
 * Kilépés : q
 * Random számú kontrolpont generálása : e
 * Random kontrolpontok generálása : r
 * Kontrolpontok számának növelése : a
 * Kontrolpontok számának csökkentése : s
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PMSIZE 30

int numberofpoints=2;
GLfloat ctrlpoints[PMSIZE][3];

float randomFloat(float minValue = 0.0f, float maxValue = 1.9f){
  float between0and1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return (minValue + between0and1 * (maxValue - minValue))-0.95;
}

int randomInt(int minValue = 2, int maxValue = (PMSIZE-1)){
    return (rand() % (maxValue - minValue + 1)) + minValue;
}

void generateRandomPoints(){
    for(int i=0; i<PMSIZE; i++){
        ctrlpoints[i][0]=randomFloat();
        ctrlpoints[i][1]=randomFloat();
    }
}
void psInit()
{
  srand(time(NULL));
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

  for(int i=0; i<PMSIZE; i++){
        ctrlpoints[i][0]=0;
        ctrlpoints[i][1]=0;
    }
}
static void psdisplay(void)
{
    int i=0;    // inkrementális változó
    glClear(GL_COLOR_BUFFER_BIT );

    //======================================================
    /*
     *  Megjelenítjük a pontmátrix elemeit
    */
    glPointSize(6);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < numberofpoints; i++){

        if(i==0){
            glColor3f(1.0,0.0,0.0); // kezdőpont - vörös
        }else if(i==numberofpoints-1){
            glColor3f(1.0,1.0,0.0); //  végpont - sárga
        }else{
            glColor3f(0.0,1.0,0.0); //  köztes pontok - zöld
        }
        glVertex3fv((GLfloat*)&ctrlpoints[i][0]);
    }
    glEnd();
    /*
     *  Pontokat összektjük egy vonallal a szemléltetés miatt
    */
    glLineWidth(0.2);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < numberofpoints; i++){
        glVertex3f(ctrlpoints[i][0],ctrlpoints[i][1],0.0);
    }
    glEnd();
    //======================================================
    /*
     *  Bezier görbe leképzése az opengl beépített eljárásával
    */
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, numberofpoints, (GLfloat*)&ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glColor3f(1.0, 0.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= (10*numberofpoints); i++){
        glEvalCoord1f((GLfloat) i/(10*numberofpoints));
    }
    glEnd();
    glFinish();
}


static void pskey(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':{
            exit(0);
            break;
        }
        case 'r':{
            generateRandomPoints();
            break;
        }
        case 'a':{
            if(numberofpoints!=(PMSIZE-1)){
                numberofpoints++;
            }
            break;
        }
        case 's':{
            if(numberofpoints!=2){
                numberofpoints--;
            }
            break;
        }
        case 'e':{
            numberofpoints=randomInt();
        }
    }
    glutPostRedisplay();
}
void printMessage(){
    printf("Grafika beadando 2020 - 2D bezier gorbe kirajzolasa\n\r");
    printf("Grebely Janos - CL4WWB - G2BIL\n\r");
    for(int k=0; k<51; k++){
        printf("*");
    }
    printf("\n\r * q - kilepes;");
    printf("\n\r * e - Random szamu kontrolpont generalasa;");
    printf("\n\r * r - Random kontrolpontok generalasa;");
    printf("\n\r * a - Kontrolpontok szamanak novelese;");
    printf("\n\r * s - Kontrolpontok szamanak csokkentese;\n\r");
    for(int k=0; k<51; k++){
        printf("*");
    }
}
int main(int argc, char *argv[])
{
    printMessage();
    glutInit(&argc, argv);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(250,250);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("me-grafika-bezier");
    psInit();
    generateRandomPoints();
    glutDisplayFunc(psdisplay);
    glutKeyboardFunc(pskey);

    glutMainLoop();

    return EXIT_SUCCESS;
}
