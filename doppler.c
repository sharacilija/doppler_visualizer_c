#include <stdio.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define MAX_WAVES 1000
#define WAVE_SPEED 100
#define CAR_SPEED 1.0f
#define WAVE_EMISSION_FREQUENCY 6 // Hertz

int current_waves = 0;

struct Car {
    float x, y;
};

struct SoundWave {
    float x, y, r;
};

struct Car car;

struct SoundWave waves[MAX_WAVES];

void DrawCar()
{
    DrawCircle(car.x, car.y, 20, RAYWHITE);
}

void Emit_New_Wave()
{
    waves[current_waves % MAX_WAVES] = (struct SoundWave) {car.x, car.y, 0};
    current_waves++;

    if (current_waves >= MAX_WAVES)
        current_waves = MAX_WAVES;
}

void draw_waves()
{
    for (int i = 0; i < current_waves; i++)
    {
        DrawCircleLines(waves[i].x, waves[i].y, waves[i].r, RAYWHITE);
    }
    
}

void Propagate_Waves(float dt)
{
    for (int i = 0; i < current_waves; i++)
    {
        waves[i].r += WAVE_SPEED * dt;
    }
    
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Doppler Simulator");

    car = (struct Car){WIDTH/2, HEIGHT/2};

    SetTargetFPS(60);
    float interval = 0;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        interval += dt;
        if (interval > 1.0f / WAVE_EMISSION_FREQUENCY)
        {
            Emit_New_Wave();
            interval = 0.0f;
        }
        Propagate_Waves(dt);

        if (IsKeyDown(KEY_RIGHT)) car.x += CAR_SPEED;
        if (IsKeyDown(KEY_LEFT)) car.x -= CAR_SPEED;
        if (IsKeyDown(KEY_UP)) car.y -= CAR_SPEED;
        if (IsKeyDown(KEY_DOWN)) car.y += CAR_SPEED;

        BeginDrawing();

        ClearBackground(BLACK);
        
        DrawCar();
        draw_waves();

        EndDrawing();
    }

    return 0;
}

/*
    after making changes, upload updates with:
    git add .
    git commit -m "Updated project"
    git push
*/
