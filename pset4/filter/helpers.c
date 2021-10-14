#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    int i, j;
    int r, g, b, tem1;
    double tem;
    
    // Iterating all the pixels and making them grey
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;
            r = image[i][j].rgbtRed;
            
            // Calculating average
            tem = (b + g + r) / 3.0;
            tem = round(tem);
            
            tem1 = (int) tem;
            
            // Assigning new values
            image[i][j].rgbtBlue = tem1;
            image[i][j].rgbtGreen = tem1;
            image[i][j].rgbtRed = tem1;
            
        }
        
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    int i, j;
    int oR, oG, oB, R, G, B;
    double sR, sG, sB;
    
    // Iterating all pixels
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            oB = image[i][j].rgbtBlue;
            oG = image[i][j].rgbtGreen;
            oR = image[i][j].rgbtRed;
            
            // formulas for sepia filter
            sR = (.393 * oR) + (.769 * oG) + (.189 * oB);
            sG = (.349 * oR) + (.686 * oG) + (.168 * oB);
            sB = (.272 * oR) + (.534 * oG) + (.131 * oB);

            // Rounding
            sR = round(sR);
            sG = round(sG);
            sB = round(sB);
            
            R = (int) sR;
            G = (int) sG;
            B = (int) sB;
            
            // Checking if outside of range or not
            if (R > 255)
            {
                R = 255;
            }

            if (G > 255)
            {
                G = 255;
            }

            if (B > 255)
            {
                B = 255;
            }
            
            // Assigning new values
            image[i][j].rgbtBlue = B;
            image[i][j].rgbtGreen = G;
            image[i][j].rgbtRed = R;
            
            
        }
      
        

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    int i, j, n, oRL, oGL, oBL, oRR, oGR, oBR, tR, tG, tB;
    
    // Iterating through all pixels
    for (i = 0; i < height; i++)
    {
        n = width - 1;
        for (j = 0; j < (width / 2); j++)
        {
            // swapping pixels
            oBL = image[i][j].rgbtBlue;
            oGL = image[i][j].rgbtGreen;
            oRL = image[i][j].rgbtRed;
            
            tB = oBL;
            tG = oGL;
            tR = oRL;
            
            oBR = image[i][n - j].rgbtBlue;
            oGR = image[i][n - j].rgbtGreen;
            oRR = image[i][n - j].rgbtRed;
            
            image[i][j].rgbtBlue = oBR;
            image[i][j].rgbtGreen = oGR;
            image[i][j].rgbtRed = oRR;
            
            image[i][n - j].rgbtBlue = tB;
            image[i][n - j].rgbtGreen = tG;
            image[i][n - j].rgbtRed = tR;
            
            
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    RGBTRIPLE copy[height][width];
    int i, j, row, col, count;
    
    int R, G, B, R2, G2, B2;
    double R1, G1, B1;
    
    // Copying image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    
    // Iterating all pixels
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            R = 0;
            G = 0;
            B = 0;
            count = 0;
            
            // Inner loop for calculating new pixel values
            for (row = i - 1; row <= i + 1; row++)
            {
                for (col = j - 1; col <= j + 1; col++)
                {
                    if ((row >= 0 && row < height) && (col >= 0 && col < width))
                    {
                        B += copy[row][col].rgbtBlue;
                        G += copy[row][col].rgbtGreen;
                        R += copy[row][col].rgbtRed;
                        count++;
                    }
                }
            }
            
            // Calculation
            B1 = (B / (double) count);
            B1 = round(B1);
            B2 = (int) B1;
            
            G1 = (G / (double) count);
            G1 = round(G1);
            G2 = (int) G1;
            
            R1 = (R / (double) count);
            R1 = round(R1);
            R2 = (int) R1;
            
            // Assigning new values
            image[i][j].rgbtBlue = B2;
            image[i][j].rgbtGreen = G2;
            image[i][j].rgbtRed = R2;
            
        }
    }
    return;
}
