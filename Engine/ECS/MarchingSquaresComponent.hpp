#pragma once
#include <random>

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include "../Parallel.hpp"

float random(float min, float max)
{
    int range = static_cast<int>(max - min);
    return (std::rand() % range) - min;
}

struct Line
{
    Vector2D start;
    Vector2D end;
    Line(Vector2D &s, Vector2D &e)
    {
        start = s;
        end = e;
    }
};

class Circle
{
public:
    float dx;
    float dy;
    float radius;
    float w = 1000;
    float h = 700;
    float speed;
    float x;
    float y;

    Circle()
    {
        speed = 40;
        dx = random(-speed, speed);
        dy = random(-speed, speed);
        x = random(0, w);
        y = random(0, h);
        radius = random(50, 200);
    }

    void update(float delta_time)
    {
        if (this->x >= this->w)
        {
            this->dx = -std::abs(this->dx);
        }
        else if (this->x <= 0)
        {
            this->dx = std::abs(this->dx);
        }

        if (this->y >= this->h)
        {
            this->dy = -std::abs(this->dy);
        }
        else if (this->y <= 0)
        {
            this->dy = std::abs(this->dy);
        }
        this->x += this->dx * delta_time;
        this->y += this->dy * delta_time;
    }
};

class MarchingSquaresComponent : public Component
{
public:
    void init() override
    {
        LINES.clear();

        int size_x = static_cast<int>(width / step) + 1;
        values = new float *[size_x];
        for (int i = 0; i < size_x; i++)
        {
            int size_y = static_cast<int>(width / step) + 1;
            values[i] = new float[size_y];
        }

        for (int i = 0; i < 10; i++)
        {
            CIRCLES.push_back(Circle());
        }
    }

    void update() override
    {
        LINES.clear();
        for (int i = 0; i < 10; i++)
        {
            CIRCLES[i].update(Game::deltaTime);
        }
        calc_values();
        marching_squares();
    }

    void draw() override
    {
        // std::cout << LINES.size() << std::endl;
        for (size_t i = 0; i < LINES.size(); i++)
        {
            SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
            SDL_RenderDrawLineF(Game::renderer, LINES[i].start.x, LINES[i].start.y, LINES[i].end.x, LINES[i].end.y);
        }
    }

    ~MarchingSquaresComponent()
    {
        int size_x = static_cast<int>(width / step) + 1;
        for (int i = 0; i < size_x; i++)
        {
            delete[] values[i];
        }
        delete[] values;
    }

private:
    std::vector<Line> LINES;
    const int width = 1000;
    const int height = 700;
    const int step = 10;
    const float level = 1;
    float **values;
    std::vector<Circle> CIRCLES;

    float calc_sumed_distances_to_circles(Vector2D &&pos)
    {
        float sum = 0;
        for (size_t i = 0; i < CIRCLES.size(); i++)
        {
            sum += (std::pow(CIRCLES[i].radius, 2) / (std::pow(pos.x - CIRCLES[i].x, 2) + std::pow(pos.y - CIRCLES[i].y, 2)));
        }
        return sum;
    }
    void calc_values()
    {
        parallel_for(static_cast<int>(width / step), [this](int s, int e)
                     { process_chunk(s, e); });
    }

    void process_chunk(int start, int end)
    {
        for (int x = start; x < end; x++)
        {
            int e = static_cast<int>(height / step);
            for (int y = 0; y < e; y++)
            {
                float dist = calc_sumed_distances_to_circles(Vector2D(x * step, y * step));
                values[x][y] = dist;
            }
        }
    }

#define LINE(v1, v2) LINES.push_back(Line(v1, v2))
    void marching_squares()
    {
        for (int x = 0; x < static_cast<int>(width / step); x++)
        {
            for (int y = 0; y < static_cast<int>(height / step); y++)
            {
                int state = get_state(values[x][y], values[x + 1][y], values[x + 1][y + 1], values[x][y + 1], level);
                Vector2D a = scale(x + 0.5, y);
                Vector2D b = scale(x + 1, y + 0.5);
                Vector2D c = scale(x + 0.5, y + 1);
                Vector2D d = scale(x, y + 0.5);
                switch (state)
                {
                case 1:
                    LINE(c, d);
                    break;
                case 2:
                    LINE(b, c);
                    break;
                case 3:
                    LINE(b, d);
                    break;
                case 4:
                    LINE(a, b);
                    break;
                case 5:
                    LINE(a, d);
                    LINE(b, c);
                    break;
                case 6:
                    LINE(a, c);
                    break;
                case 7:
                    LINE(a, d);
                    break;
                case 8:
                    LINE(a, d);
                    break;
                case 9:
                    LINE(a, c);
                    break;
                case 10:
                    LINE(a, b);
                    LINE(c, d);
                    break;
                case 11:
                    LINE(a, b);
                    break;
                case 12:
                    LINE(b, d);
                    break;
                case 13:
                    LINE(b, c);
                    break;
                case 14:
                    LINE(c, d);
                    break;
                }
            }
        }
    }
    Vector2D scale(float x, float y)
    {
        return Vector2D(x * step, y * step);
    }
#define CHECK(x, y, z, w) if (a x level && b y level && c z level && d w level)
    int get_state(int a, int b, int c, int d, float level)
    {
        CHECK(<, <, <, <)
        return 0;
        CHECK(<, <, <, >=)
        return 1;
        CHECK(<, <, >=, <)
        return 2;
        CHECK(<, <, >=, >=)
        return 3;
        CHECK(<, >=, <, <)
        return 4;
        CHECK(<, >=, <, >=)
        return 5;
        CHECK(<, >=, >=, <)
        return 6;
        CHECK(<, >=, >=, >=)
        return 7;
        CHECK(>=, <, <, <)
        return 8;
        CHECK(>=, <, <, >=)
        return 9;
        CHECK(>=, <, >=, <)
        return 10;
        CHECK(>=, <, >=, >=)
        return 11;
        CHECK(>=, >=, <, <)
        return 12;
        CHECK(>=, >=, <, >=)
        return 13;
        CHECK(>=, >=, >=, <)
        return 14;
        CHECK(>=, >=, >=, >=)
        return 15;
    }
};