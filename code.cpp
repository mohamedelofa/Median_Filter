#include <iostream>
#include <fstream>
#include<vector>
#include<string>

using namespace std;

int width , height , maxvalue;

struct pixel{
    int r , g , b;
};


void InsertionSort(vector<int> &arr){
    for(int i = 1 ; i < arr.size() ; i++){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && key < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1 ] = key;
    }
}

int median(vector<int> &window){
    InsertionSort(window);
    return window[window.size() / 2];
}

vector<vector<pixel>> readImage(const string &filename , int kernelSize){
    ifstream file(filename.c_str() , ios::in);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename.c_str() << endl;
        exit(EXIT_FAILURE);
    }
    string format;
    file >> format;
    file >> width;
    file >> height;
    file >> maxvalue;
    int padding = kernelSize / 2;
    vector<vector<pixel>> image(height + 2 * padding, vector<pixel>(width + 2 * padding ));

    for(int i = padding ; i < height + padding ; i++){
        for(int j = padding ; j <  width + padding ; j++){
            file >> image[i][j].r >> image[i][j].g >> image[i][j].b;
        }
    }

      // add padding for first and last rows
    for (int j = padding; j < width + 2 * padding; j++) {
        for (int p = 0; p < padding; p++) {
            // first
            image[p][j] = image[padding][j];
            // last
            image[height + padding + p][j] = image[height + padding - 1][j];
        }
    }

    // add padding for first and last columns
    for (int i = 0; i < height + 2 * padding; i++) {
        for (int p = 0; p < padding; p++) {
            // first
            image[i][p] = image[i][padding];
            // last
            image[i][width + padding + p] = image[i][width + padding - 1];
        }
    }

    file.close();

    return image;
}

vector<vector<pixel>> ApplyMedianFilter(vector<vector<pixel>> &image , int kernelSize){
    int padding = kernelSize / 2;
    vector<vector<pixel>> filteredImage(height , vector<pixel>(width));
    for(int i = padding ; i < height + padding; i++){
        for(int j = padding ; j < width + padding ; j++){
            vector<int> red, green , blue;
            for (int ki = -padding; ki <= padding; ki++) {
                for (int kj = -padding; kj <= padding; kj++) {
                red.push_back(image[i + ki][j + kj].r);
                green.push_back(image[i + ki][j + kj].g);
                blue.push_back(image[i + ki][j + kj].b);
            }
        }
        filteredImage[i - padding][j - padding].r = median(red);
        filteredImage[i - padding][j - padding].g = median(green);
        filteredImage[i - padding][j - padding].b = median(blue);
        }
    }
    return filteredImage;
}

void SaveImage(string &output , vector<vector<pixel>> &filteredimage){
    ofstream file(output.c_str());
    file << "P3\n" << width << " " << height << "\n" << maxvalue << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << filteredimage[i][j].r << " " << filteredimage[i][j].g << " " << filteredimage[i][j].b << " ";
        }
        file << "\n";
    }
    file.close();
}

int main(){

    // image file
    string noisyfile = "noisy.ppm";
    string outputfile = "noisyoutput.ppm";

    int kernelSize = 3;
    // read image
    vector<vector<pixel>> noisyimage = readImage(noisyfile , kernelSize);


    vector<vector<pixel>> filteredImage = ApplyMedianFilter(noisyimage , kernelSize);

    SaveImage(outputfile , filteredImage);

    cout << "Done" << endl;

    // for(int i = 0 ; i <= 1 ; i++){
    //     for(int j = 0 ; j <= 6 ; j++){
    //         cout << noisyimage[i][j].r << " " <<  noisyimage[i][j].g << " " << noisyimage[i][j].b << " ";
    //     }
    //     cout << endl;
    // }
}