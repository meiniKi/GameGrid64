#ifndef GOL_H_
#define GOL_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Playable.h"
#include <stdlib.h>

template <uint16_t Rows, uint16_t Cols>
class GoL {
private:
    // o3o2o1o0,n3n2n1n0
    uint8_t grid_[Rows][Cols];

    uint32_t alive_(uint16_t i, uint16_t j);
    void age_();
    void newGen_();

public:
    GoL();
    void next();
    void randGrid(uint64_t seed, uint8_t density_thresh);
    void render(Adafruit_GFX* gfx, uint16_t color);
};



template <uint16_t Rows, uint16_t Cols>
GoL<Rows, Cols>::GoL()
{
    // Constructor implementation
}

template <uint16_t Rows, uint16_t Cols>
void GoL<Rows, Cols>::randGrid(uint64_t seed, uint8_t density_thresh)
{
    if (seed != 0)
        srand(seed);
    
    for (uint16_t i=0; i<Rows; i++)
    {
        for (uint16_t j=0; j<Cols; j++)
        {
            grid_[i][j] =   //(((uint8_t)(rand()) < density_thresh) << 3) | 
                            //(((uint8_t)(rand()) < density_thresh) << 2) | 
                            //(((uint8_t)(rand()) < density_thresh) << 1) | 
                            (((uint8_t)(rand()) < density_thresh));
        }
    }
}

template <uint16_t Rows, uint16_t Cols>
uint32_t GoL<Rows, Cols>::alive_(uint16_t i, uint16_t j)
{
    uint8_t c[4] = {0,0,0,0};

    for (int32_t di = -1; di <= 1; di++)
    {
        for (int32_t dj = -1; dj <= 1; dj++)
        {
            if ((di == 0) && (dj == 0)) continue;
            uint16_t ni = ((int32_t)(i) + di + (int32_t)(Rows)) % Rows;
            uint16_t nj = ((int32_t)(j) + dj + (int32_t)(Cols)) % Cols;
            c[0] += (grid_[ni][nj]>>4) % 2;
            c[1] += (grid_[ni][nj]>>5) % 2;
            c[2] += (grid_[ni][nj]>>6) % 2;
            c[3] += (grid_[ni][nj]>>7) % 2;
        }
    }
    return (c[3] << 24) | (c[2] << 16) | (c[1] << 8) | c[0];
}

template <uint16_t Rows, uint16_t Cols>
void GoL<Rows, Cols>::age_()
{
    for (uint16_t i = 0; i < Rows; i++)
    {
        for (uint16_t j = 0; j < Cols; j++)
        {
            grid_[i][j] <<= 4;
        }
    }
}

template <uint16_t Rows, uint16_t Cols>
void GoL<Rows, Cols>::newGen_()
{
    for (uint16_t i = 0; i < Rows; i++)
    {
        for (uint16_t j = 0; j < Cols; j++)
        {
            uint32_t alive = alive_(i, j);
            uint8_t a[4] = {
                ((uint8_t)(alive       & 0xFF)),
                ((uint8_t)((alive>> 8) & 0xFF)),
                ((uint8_t)((alive>>16) & 0xFF)),
                ((uint8_t)((alive>>24) & 0xFF)),
            };
            
            for (uint8_t c = 0; c < 1; c++)
            {
                // alive if alive and (2 or 3) neighbors
                if (((a[c]==2)||(a[c]==3)) && (((grid_[i][j] >> (4+c)) % 2)==1))
                    grid_[i][j] |= (1 << c);
                
                // alive if dead and 3 neighbors
                if ((a[c]==3) && (((grid_[i][j] >> (4+c)) % 2)==0))
                    grid_[i][j] |= (1 << c);
            }
        }
    }
}

template <uint16_t Rows, uint16_t Cols>
void GoL<Rows, Cols>::next()
{
    age_();
    newGen_();
}


template <uint16_t Rows, uint16_t Cols>
void GoL<Rows, Cols>::render(Adafruit_GFX* gfx, uint16_t color)
{
    // only render c0 in white for now
    for (uint16_t i = 0; i < Rows; i++)
    {
        for (uint16_t j = 0; j < Cols; j++)
        {
            if (grid_[i][j] % 2)
            {
                gfx->drawPixel(i, j, color);
            }
        }
    }
}


#endif // GOL_H_