#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      int average;
      average = (int) round(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtBlue);

        image[i][j].rgbtGreen = average;
        image[i][j].rgbtBlue = average;
        image[i][j].rgbtRed = average;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      int originalRed = image[i][j].rgbtRed;
      int originalGreen = image[i][j].rgbtGreen;
      int originalBlue = image[i][j].rgbtBlue;
      
      image[i][j].rgbtRed = fmin(255, (int) round((.393 * originalRed + .769 * originalGreen +.189 * originalBlue)));
      image[i][j].rgbtGreen = fmin(255, (int) round((.349 * originalRed + .686 * originalGreen + .168 * originalBlue)));
      image[i][j].rgbtBlue = fmin(255, (int) round((.272 * originalRed + .534 * originalGreen + .131 * originalBlue)));
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width / 2; j++)
    {
      RGBTRIPLE temp = image[i][j];
      image[i][j] = image[i][width - 1 -j];
      image[i][width - 1 - j] = temp; 
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  // making a temporary variable
  RGBTRIPLE temp[height][width];

  // loop  through the rows
  for (int i = 0; i < height; i++)
  {
    // loop  through the columns
    for (int j = 0; j < width; j++)
    {
      // assigning value of current pixels to temp
      temp[i][j] = image[i][j];
    }
  }
  // loop  through the rows
  for (int i = 0; i < height; i++)
  {
    // loop  through the columns
    for (int j = 0; j < width; j++)
    {
      // new variable to store value of colours
      int totalRed = 0, totalGreen = 0, totalBlue = 0;

      // counter to store the count
      float counter = 0.0;

      // loops to get 3X3 area around the pixel
      // here x and y are acting as cordinates
      for (int x = -1; x < 2; x++)
      {
        for (int y = -1; y < 2; y++)
        {
          int currentX = i + x;
          int currentY = j + y;

          // checking if the currentX and currentY are within the image only
          if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
          {
            // if not we skip it
            continue;
          }
          // getting total amount of red around the pixel in 3X3 area
          totalRed += image[currentX][currentY].rgbtRed;

          // getting total amount of green around the pixel in 3X3 area
          totalGreen += image[currentX][currentY].rgbtGreen;

          // getting total amount of blue around the pixel in 3X3 area
          totalBlue += image[currentX][currentY].rgbtBlue;
          // getting the number of pixel in 3X3 area which are within feasible range
          counter++;
        }
      }
      // setting the temp colour value same to the average of colour around it
      temp[i][j].rgbtRed = round(totalRed / counter);
      temp[i][j].rgbtGreen = round(totalGreen / counter);
      temp[i][j].rgbtBlue = round(totalBlue / counter);
    }
  }
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        // setting the new pixel value to the average value
        image[i][j] = temp[i][j];
      }
    }
  return;
}
