#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

void reverse(RGBTRIPLE *arr, int start, int end)
{
    RGBTRIPLE temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        reverse(image[i], 0, width - 1);
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int totalBlue = 0;
            int totalRed = 0;
            int totalGreen = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalBlue += tempImage[ni][nj].rgbtBlue;
                        totalRed += tempImage[ni][nj].rgbtRed;
                        totalGreen += tempImage[ni][nj].rgbtGreen;
                        count++;
                    }
                }
            }

            image[i][j].rgbtBlue = round((float) totalBlue / count);
            image[i][j].rgbtRed = round((float) totalRed / count);
            image[i][j].rgbtGreen = round((float) totalGreen / count);
        }
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j] = image[i][j];
        }
    }

    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalBlueX = 0;
            int totalRedX = 0;
            int totalGreenX = 0;
            int totalBlueY = 0;
            int totalRedY = 0;
            int totalGreenY = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalBlueX += tempImage[ni][nj].rgbtBlue * gx[di + 1][dj + 1];
                        totalRedX += tempImage[ni][nj].rgbtRed * gx[di + 1][dj + 1];
                        totalGreenX += tempImage[ni][nj].rgbtGreen * gx[di + 1][dj + 1];

                        totalBlueY += tempImage[ni][nj].rgbtBlue * gy[di + 1][dj + 1];
                        totalRedY += tempImage[ni][nj].rgbtRed * gy[di + 1][dj + 1];
                        totalGreenY += tempImage[ni][nj].rgbtGreen * gy[di + 1][dj + 1];
                    }
                }
            }

            float blue = sqrt(totalBlueX * totalBlueX + totalBlueY * totalBlueY);
            float red = sqrt(totalRedX * totalRedX + totalRedY * totalRedY);
            float green = sqrt(totalGreenX * totalGreenX + totalGreenY * totalGreenY);

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                if (blue < 0)
                {
                    image[i][j].rgbtBlue = 0;
                }
                else
                {
                    image[i][j].rgbtBlue = round(blue);
                }
            }

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                if (red < 0)
                {
                    image[i][j].rgbtRed = 0;
                }
                else
                {
                    image[i][j].rgbtRed = round(red);
                }
            }

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                if (blue < 0)
                {
                    image[i][j].rgbtGreen = 0;
                }
                else
                {
                    image[i][j].rgbtGreen = round(green);
                }
            }
        }
    }


    return;
}
