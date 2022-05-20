#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FRAND rand()/(1.0 + RAND_MAX) // Random number between 0 and 1

#define L 100 // Linear size of the square grid

void update(int state[L][L], int newstate[L][L]){
    /*
     Takes a given state of the grid and evaluates the new state.
     The grid has periodic boundary conditions.
     */
    int x, y, sumneighbours;
    
    for(x = 0; x < L; x++){
        for(y = 0; y < L; y++){
            
            sumneighbours = 0;
            
            // Right neighbour
            if(y + 1 == L){
                sumneighbours += state[x][0];
            }
            else{
                sumneighbours += state[x][y+1];
            }
            
            // Left neighbour
            if(y - 1 < 0){
                sumneighbours += state[x][L-1];
            }
            else{
                sumneighbours += state[x][y-1];
            }
            
            // Bottom neighbour
            if(x + 1 == L){
                sumneighbours += state[0][y];
            }
            else
                sumneighbours += state[x+1][y];
            
            // Upper neighbour
            if(x - 1 < 0){
                sumneighbours += state[L-1][y];
            }
            else{
                sumneighbours += state[x-1][y];
            }
            
            // Upper-right neighbour
            if(y + 1 == L && x - 1 < 0 ){
                sumneighbours += state[L-1][0];
            }
            else if(y + 1 == L && x - 1 > 0){
                sumneighbours += state[x-1][0];
            }
            else if(y + 1 != L && x - 1 < 0){
                sumneighbours += state[L-1][y+1];
            }
            else{
                sumneighbours += state[x-1][y+1];
            }
            
            // Bottom-right neighbour
            if(y + 1 == L && x + 1 == L ){
                sumneighbours += state[0][0];
            }
            else if(y + 1 == L && x + 1 != L){
                sumneighbours += state[x+1][0];
            }
            else if(y + 1 != L && x + 1 == L){
                sumneighbours += state[0][y+1];
            }
            else{
                sumneighbours += state[x+1][y+1];
            }
            
            // Upper-left neighbour
            if(y - 1 < 0 && x - 1 < 0){
                sumneighbours += state[L-1][L-1];
            }
            else if(y - 1 < 0 && x - 1 >= 0){
                sumneighbours += state[x-1][L-1];
            }
            else if(y - 1 > 0 && x - 1 < 0){
                sumneighbours += state[L-1][y-1];
            }
            else{
                sumneighbours += state[x-1][y-1];
            }
            
            // Bottom-left neighbour
            if(y - 1 < 0 && x + 1 == L){
                sumneighbours += state[0][L-1];
            }
            else if(y - 1 < 0 && x + 1 != L){
                sumneighbours += state[x+1][L-1];
            }
            else if(y - 1 >= 0 && x + 1 == L){
                sumneighbours += state[0][y-1];
            }
            else{
                sumneighbours += state[x+1][y-1];
            }
            
            // Applying the update rules
            
            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (state[x][y] == 1 && sumneighbours < 2){
                newstate[x][y] = 0;
            }
            
            // Any live cell with two or three live neighbours lives on to the next generation.
            if (state[x][y] == 1 && (sumneighbours == 2 || sumneighbours == 3) ){
                newstate[x][y] = 1;
            }
            
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (state[x][y] == 1 && sumneighbours > 3){
                newstate[x][y] = 0;
            }
            
            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if(state[x][y] == 0 && sumneighbours == 3){
                newstate[x][y] = 1;
            }
            
        }
    }
    
    
}

void initGnuplot(){
    /*
     Gives gnuplot the display configurations
     */
    double size_factor = 10.0;
    double fac = size_factor*100/L;
    int size = fac*L;
  
    printf("set term qt enhanced font 'Verdana,20'\n");
    printf("set term qt size %d,%d\n",size,size);
    printf("set size square\n");
    printf("set xrange [0:%d]\n", L);
    printf("set yrange [0:%d]\n", L);
    printf("unset xtics\n");
    printf("unset ytics\n");
    printf("unset key\n");
    printf("unset grid\n");
    printf("set pointsize %f\n",0.1*fac);
    
    
    
}

void printGnuplot(int state[L][L], int t){
    /*
     Prints a given state of the grid via gnuplot
     */
    int ix, iy;
    
    printf("set title 't = %d'  \n", t);
    printf("p '-' u 1:2 w p pt 5 lc -1\n");
    
    for(ix = 0; ix < L; ix++){
        for(iy = 0; iy < L; iy++){
            if( state[ix][iy] == 1){
                printf("%d %d\n", ix, iy);
            }
            
        }
    }
    
    printf("e\n");
}

void createBlinker(int state[L][L], int xc, int yc){
    state[xc][yc] = 1;
    state[xc][yc+1] = 1;
    state[xc][yc-1] = 1;
}

void createGlider(int state[L][L], int xc, int yc){
    state[xc][yc-1] = 1;
    state[xc-1][yc] = 1;
    state[xc+1][yc-1] = 1;
    state[xc+1][yc] = 1;
    state[xc+1][yc+1] = 1;
}


void initRandom(int state[L][L]){
    /*
     Initializes the grid with random living and dead cells 
     */
    
    int ix, iy;
    double r;
    
    for(ix = 0; ix < L; ix++){
        for(iy = 0; iy < L; iy++){
            r = FRAND;
            if(r < 0.5){
                state[ix][iy] = 1;
            }
            
        }
    }
}


int main(void){
    
    int x, y; // Coordinates in the grid
    int state[L][L]={0}; // Initial state
    int newstate[L][L]={0}; // New  state
    int t, tmax;
    
    // Set random number seed
    srand(111);
    
    // Simulation time
    tmax = 10000;
    
    // Applying random initial condition
    initRandom(state);
    
    
    initGnuplot();
    
    // System evolution
    for(t = 0; t < tmax; t++){
        
        printGnuplot(state, t);
        
        update(state, newstate);
        
        // Swaps: newstate --> state
        for(x = 0; x < L; x++){
            for(y = 0; y < L; y++){
                state[x][y] = newstate[x][y];
                
            }
        }
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
