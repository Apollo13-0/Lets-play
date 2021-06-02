#ifndef SERVER_DIVIDEIMAGE_H
#define SERVER_DIVIDEIMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/core/mat.hpp>
#include <math.h>

/*!
 * \brief Checks if the number is a perfect square
 *
 * \param n int
 */
bool isSquare(int n)
{
    if (ceil((double)sqrt(n)) == floor((double)sqrt(n)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Checks if the number is a power of 2
 *
 * \param n int
 */
bool isPowerOf2(int n)
{
    if (ceil(log2(n)) == floor(log2(n)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
* \brief divides de image
* \param int division number
* \param image
* \param blocks
*/
int divideImage(const cv::Mat& img, int numDiv, std::vector<cv::Mat>& blocks)
{
    std::cout << img.empty() << "  efdsdf"<<endl;
    // Checking if the image was passed correctly
    if (!img.data || img.empty())
    {
        std::wcout << "Image Error: Cannot load image to divide." << std::endl;
        return EXIT_FAILURE;
    }

    // init image dimensions
    int imgWidth = img.cols;
    int imgHeight = img.rows;
    std::wcout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;


    // init block dimensions
    int bhSize; // These are going to be the size of each chunk's rows and columns (width and height)
    int bwSize;

    int blockWidth;
    int blockHeight;

    if (isSquare(numDiv))
    {
        blockHeight = floor(imgHeight / sqrt(numDiv));
        blockWidth = floor(imgWidth / sqrt(numDiv));
    }
    else if (isPowerOf2(numDiv))
    {
        blockHeight = floor(imgHeight / sqrt(numDiv / 2));
        blockWidth = floor(imgWidth / sqrt(numDiv * 2));
    }




    int y0 = 0;

    while (y0 < imgHeight)
    {
        // agregar una condicion que verifique que x0 y y0 no tenga 1 o 2 pixel
        // compute the block height
        bhSize = ((y0 + blockHeight) > imgHeight) * (blockHeight - (y0 + blockHeight - imgHeight)) + ((y0 + blockHeight) <= imgHeight) * blockHeight;

        int x0 = 0;
        while (x0 < imgWidth)

        {
            // compute the block height
            bwSize = ((x0 + blockWidth) > imgWidth) * (blockWidth - (x0 + blockWidth - imgWidth)) + ((x0 + blockWidth) <= imgWidth) * blockWidth;
            std::cout<< bwSize << "    " << imgWidth;
            // crop block
            blocks.push_back(img(cv::Rect(x0, y0, bwSize, bhSize)).clone());

            // update x-coordinate
            x0 = x0 + blockWidth;
            std::cout<< x0 <<endl;
        }

        // update y-coordinate
        y0 = y0 + blockHeight;
    }
    return EXIT_SUCCESS;
}




#endif //SERVER_DIVIDEIMAGE_H
