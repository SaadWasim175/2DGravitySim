#include "raylib.h"
#include <math.h>

// for orbit at distance dist, orbital velocity would be 447 * sqrt(400/R) 
//if you change masses way too much just use dist = GM/v² to find the best distance at which the masses would orbit each other
// in r = GM/v² M would be mass of larger mass in unequal masses and M would be mass of either mass in equal masses.


typedef struct {
    float x, y;
    float vx, vy;
    float mass;
    float radius;
    Color color;
} Mass;

void updateMassPosition(Mass* mass, float dt, int screenWidth, int screenHeight) {
    //toroidal wraparounds to make sure masses dont disappear off scren
    if (mass->x < -mass->radius) mass->x = screenWidth + mass->radius;
    if (mass->x > screenWidth + mass->radius) mass->x = -mass->radius;
    if (mass->y < -mass->radius) mass->y = screenHeight + mass->radius;
    if (mass->y > screenHeight + mass->radius) mass->y = -mass->radius;
    
    mass->x += mass->vx * dt;
    mass->y += mass->vy * dt;
}

void applyGravity(Mass* mass1, Mass* mass2, float G, float dt) {
    float dx = mass2->x - mass1->x;
    float dy = mass2->y - mass1->y;
    float dist = sqrtf(dx*dx + dy*dy);
    
    if (dist < 0.001f) dist = 0.001f;
    
    float ux = dx / dist;
    float uy = dy / dist;
    
    float a1 = G * mass2->mass / (dist * dist);
    
    mass1->vx += ux * a1 * dt;
    mass1->vy += uy * a1 * dt;
}

void drawMass(Mass* mass) {
    DrawCircle(mass->x, mass->y, mass->radius, mass->color);
}

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "Planet Sim");
    SetTargetFPS(60);

    Mass planet = {1360, 540, 0, 0, 25, 25, WHITE};
    Mass star = {960, 540, 0, 0, 1000, 100, RED};


    float dx = star.x - planet.x;
    float dy = star.y - planet.y;
    float dist = sqrtf(dx*dx + dy*dy);
    if (planet.mass == star.mass) {
        float singleMass = planet.mass;
        float orbitalVel = sqrtf(80000 * singleMass / (2.0f * dist));
        planet.vy = orbitalVel;
        star.vy = -orbitalVel;
    } else {
        planet.vy = 447 * sqrtf(400.0f / dist);
        star.vy = 0; 
    }
    
    float G = 80000;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        applyGravity(&planet, &star, G, dt);
        applyGravity(&star, &planet, G, dt); 
        
        updateMassPosition(&planet, dt, screenWidth, screenHeight);
        updateMassPosition(&star, dt, screenWidth, screenHeight);

        BeginDrawing();
            ClearBackground(BLACK);
            drawMass(&planet);
            drawMass(&star);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}