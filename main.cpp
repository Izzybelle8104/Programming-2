#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// READ DATA
class Image_Processing {
public:
    Image_Processing() = default;

// STORE DATA -------------------------------------------------------------------------------
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Image_Data {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    };

//READ DATA -------------------------------------------------------------------------------
    void read_header(ifstream &file, Header &header, vector<Image_Data> &image_data) {
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read((char *) &header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.read((char *) &header.colorMapLength, sizeof(header.colorMapLength));
        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read((char *) &header.xOrigin, sizeof(header.xOrigin));
        file.read((char *) &header.yOrigin, sizeof(header.yOrigin));
        file.read((char *) &header.width, sizeof(header.width));
        file.read((char *) &header.height, sizeof(header.height));
        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        int counter = (int) header.width * (int) header.height;

        //image_data
        for (int i = 0; i < counter; ++i) {
            Image_Data pixels;
            file.read((char *) &pixels.blue, sizeof(pixels.blue));
            file.read((char *) &pixels.green, sizeof(pixels.green));
            file.read((char *) &pixels.red, sizeof(pixels.red));
            image_data.push_back(pixels);

        }

    }

//WRITE A FILE

    void write_file(Header &header_array,vector<Image_Data> &Image_data,ofstream &outfile){
        outfile.write (&header_array.idLength, sizeof(header_array.idLength));
        outfile.write(&header_array.colorMapType, sizeof(header_array.colorMapType));
        outfile.write(&header_array.dataTypeCode, sizeof(header_array.dataTypeCode));
        outfile.write((char*)&header_array.colorMapOrigin, sizeof(header_array.colorMapOrigin));
        outfile.write((char*)&header_array.colorMapLength, sizeof(header_array.colorMapLength));
        outfile.write(&header_array.colorMapDepth, sizeof(header_array.colorMapDepth));
        outfile.write((char*)&header_array.xOrigin, sizeof(header_array.xOrigin));
        outfile.write((char*)&header_array.yOrigin, sizeof(header_array.yOrigin));
        outfile.write((char*)&header_array.width, sizeof(header_array.width));
        outfile.write((char*)&header_array.height, sizeof(header_array.height));
        outfile.write(&header_array.bitsPerPixel, sizeof(header_array.bitsPerPixel));
        outfile.write(&header_array.imageDescriptor, sizeof(header_array.imageDescriptor));

        for (size_t i = 0; i < Image_data.size(); ++i) {
            Image_Processing::Image_Data &pixel = Image_data[i];
            outfile.write((char *) (&pixel.blue), sizeof(pixel.blue));
            outfile.write((char *) (&pixel.green), sizeof(pixel.green));
            outfile.write((char *) (&pixel.red), sizeof(pixel.red));
        }

    }

//ALGORITHMS -------------------------------------------------------------------------------

    //multiply
    vector<Image_Data> multiply(vector<Image_Data> &image_data_1, vector<Image_Data> &image_data_2, int size) {
        vector<Image_Data> multiplied_result;
        float new_blue;
        float new_green;
        float new_red;

        for (int i = 0; i < size; ++i) {
            Image_Data new_pixel;
            float blue_1 = (float(image_data_1[i].blue) / 255);
            float green_1 = (float(image_data_1[i].green) / 255);
            float red_1 = (float(image_data_1[i].red) / 255);
            float blue_2 = (float(image_data_2[i].blue) / 255);
            float green_2 = (float(image_data_2[i].green) / 255);
            float red_2 = (float(image_data_2[i].red) / 255);

            //operation

            //BLUE ---------------------------------------------------------------------------
            new_blue = (((blue_1 * blue_2) * 255) + 0.5f);

            //clamp
            if (new_blue < 0){
                new_blue = 0;
            }

            if (new_blue > 255){
                new_blue = 255;
            }
            new_pixel.blue = (unsigned char) new_blue;
            //GREEN ---------------------------------------------------------------------------
            new_green = (((green_1 * green_2) * 255) + 0.5f);

            //clamp
            if (new_green < 0){
                new_green = 0;
            }
            if (new_green > 255){
                new_green = 255;
            }
            new_pixel.green = (unsigned char) new_green;
            //RED ---------------------------------------------------------------------------
            new_red = (((red_1 * red_2) * 255) + 0.5f);

            //clamp
            if (new_red < 0){
                new_red = 0;
            }
            if (new_red > 255){
                new_red = 255;
            }
            new_pixel.red = (unsigned char) new_red;
            //-------------------------------------
            multiplied_result.push_back(new_pixel);
        }

        return multiplied_result;
    }

    //screen
    vector<Image_Data> screen (vector<Image_Data>& image_data_1, vector<Image_Data>& image_data_2, int size){
        vector<Image_Data> screen_result;
        float new_blue;
        float new_green;
        float new_red;

        for (int i = 0; i < size ; ++i){
            Image_Data new_pixel;
            float blue_1 = (float(image_data_1[i].blue) / 255);
            float green_1 = (float(image_data_1[i].green) / 255);
            float red_1 = (float(image_data_1[i].red) / 255);
            float blue_2 = (float(image_data_2[i].blue) / 255);
            float green_2 = (float(image_data_2[i].green) / 255);
            float red_2 = (float(image_data_2[i].red) / 255);

            //operation

            //BLUE ---------------------------------------------------------------------------
            new_blue = (((1 - (1 - blue_1) * (1 - blue_2)) * 255) + 0.5f);

            //clamp
            if (new_blue < 0){
                new_blue = 0;
            }

            if (new_blue > 255){
                new_blue = 255;
            }
            new_pixel.blue = (unsigned char) new_blue;

            //GREEN ---------------------------------------------------------------------------
            new_green = (((1 - (1 - green_1) * (1 - green_2)) * 255) + 0.5f);

            //clamp
            if (new_green < 0){
                new_green = 0;
            }
            if (new_green > 255){
                new_green = 255;
            }
            new_pixel.green = (unsigned char) new_green;

            //RED ---------------------------------------------------------------------------
            new_red = (((1 - (1 - red_1) * (1 - red_2)) * 255) + 0.5f);

            //clamp
            if (new_red < 0){
                new_red = 0;
            }
            if (new_red > 255){
                new_red = 255;
            }
            new_pixel.red = (unsigned  char) new_red;
            //-------------------------------
            screen_result.push_back(new_pixel);
        }

        return screen_result;
    }

    //subtract
    vector<Image_Data> subtract (vector<Image_Data>  &image_data_1, vector<Image_Data> &image_data_2, int size){
        vector<Image_Data> subtract_result;
        int new_blue;
        int new_green;
        int new_red;

        for (int i = 0; i < size ; ++i){
            Image_Data new_pixel;
            int blue_1 = ((int)image_data_1[i].blue);
            int green_1 = ((int)image_data_1[i].green);
            int red_1 = ((int)image_data_1[i].red);
            int blue_2 = (int(image_data_2[i].blue));
            int green_2 = (int(image_data_2[i].green));
            int red_2 = (int(image_data_2[i].red));

            //operations

            //BLUE ---------------------------------------------------------------------------
            new_blue = blue_1 - blue_2;
            if (new_blue < 0){
                new_blue = 0;
            }
            new_pixel.blue = (unsigned char) new_blue;

            //GREEN ---------------------------------------------------------------------------
            new_green = green_1 - green_2;
            if (new_green < 0){
                new_green = 0;
            }
            new_pixel.green = (unsigned char) new_green;

            //RED ---------------------------------------------------------------------------
            new_red = red_1 - red_2;
            if (new_red < 0){
                new_red = 0;
            }
            new_pixel.red = (unsigned  char) new_red;
            //-----------------------------------
            subtract_result.push_back(new_pixel);
        }

        return subtract_result;
    }

    //addition
    vector<Image_Data> addition (vector<Image_Data>& image_data_1, int size){
        vector<Image_Data> addition_result;
        int new_green;

        for (int i = 0; i < size ; ++i){
            Image_Data new_pixel;
            int blue_1 = ((int)image_data_1[i].blue);
            int green_1 = ((int)image_data_1[i].green);
            int red_1 = ((int)image_data_1[i].red);

            //operation
            new_green = green_1 + 200;
            if (new_green > 255){
                new_green = 255;
            }
            new_pixel.blue = (unsigned char) blue_1;
            new_pixel.green = (unsigned char) new_green;
            new_pixel.red = (unsigned  char) red_1;

            addition_result.push_back(new_pixel);

        }

        return addition_result;
    }


    //overlay
    vector<Image_Data> overlay (vector<Image_Data>& image_data_1, vector<Image_Data>& image_data_2, int size){
        vector<Image_Data> overlay_result;
        float new_blue;
        float new_green;
        float new_red;

        for (int i = 0; i < size ; ++i){
            Image_Data new_pixel;
            float blue_1 = (float(image_data_1[i].blue) / 255);
            float green_1 = (float(image_data_1[i].green) / 255);
            float red_1 = (float(image_data_1[i].red) / 255);
            float blue_2 = (float(image_data_2[i].blue) / 255);
            float green_2 = (float(image_data_2[i].green) / 255);
            float red_2 = (float(image_data_2[i].red) / 255);

            //operation

            //BLUE ---------------------------------------------------------------------------
            if (blue_2 <= 0.5){
                new_blue = (((2 * blue_1 * blue_2) * 255) + 0.5f);            }
            else{
                new_blue = (((1 - (2 * (1 - blue_1) * (1 - blue_2))) * 255) + 0.5f);

            }

            //clamp
            if (new_blue < 0){
                new_blue = 0;
            }

            if (new_blue > 255){
                new_blue = 255;
            }

            new_pixel.blue = (unsigned char) new_blue;

            //GREEN ---------------------------------------------------------------------------
            if (green_2 <= 0.5){
                new_green = (((2 * green_1 * green_2) * 255) + 0.5f);
            }
            else{
                new_green = (((1 - (2 * (1 - green_1) * (1 - green_2))) * 255) + 0.5f);
            }

            //clamp
            if (new_green < 0){
                new_green = 0;
            }
            if (new_green > 255){
                new_green = 255;
            }

            new_pixel.green = (unsigned char) new_green;

            //RED ---------------------------------------------------------------------------
            if (red_2 <= 0.5){
                new_red = (((2 * red_1 * red_2) * 255) + 0.5f);
            }
            else{
                new_red = (((1 - (2 * (1 - red_1) * (1 - red_2))) * 255) + 0.5f);

            }

            //clamp
            if (new_red < 0){
                new_red = 0;
            }
            if (new_red > 255){
                new_red = 255;
            }

            new_pixel.red = (unsigned char) new_red;

            //------------------------------
            overlay_result.push_back(new_pixel);

        }

        return overlay_result;
    }

//TASKS ----------------------------------------------------------------------------------------------------------------


};

int main() {

    //VARIABLES -------------------------------------------------------------------------------
    Image_Processing read;

    string paths[] = {
            "../input/text2.tga",
            "../input/car.tga",
            "../input/circles.tga",
            "../input/layer_blue.tga",
            "../input/layer_green.tga",
            "../input/layer_red.tga",
            "../input/layer1.tga",
            "../input/layer2.tga",
            "../input/pattern1.tga",
            "../input/pattern2.tga",
            "../input/text.tga"
    };

    //array of each image header and image data
    ifstream files[11];

    //array of structs containing headers
    Image_Processing::Header header_array[11];

    //array of vectors with Image_Data structs
    vector<Image_Processing::Image_Data> image_data_array[11];

    //LOAD FILES -------------------------------------------------------------------------------
    for (int i = 0; i < 11; ++i) {
        files[i].open(paths[i], ios::binary);
        if (!files[i].is_open()) {
            std::cerr << "Error opening file: " << paths[i] << std::endl;
            return 1;
        }
    }

    //READ DATA -------------------------------------------------------------------------------
    for (int i = 0; i < 11; ++i) {
        read.read_header(files[i], header_array[i], image_data_array[i]);

    }

//WRITE NEW FILE -------------------------------------------------------------------------------

    string input = "";
    string tasks = "";

    while (input != "Q") {
        cout << "Choose a task to output a new image:" << endl;
        cout << "1. Multiply 2 image's pixels into a new image" << endl;
        cout << "2. Subtract 2 image's pixels into a new image" << endl;
        cout << "3. Multiply 2 image's pixels into a new image, and then screen the image with another to produce a new one" << endl;
        cout << "4. Multiply 2 image's pixels into a new image, and then subtract the image with another to produce a new one" << endl;
        cout << "5. Overlay 2 image's pixels into a new image" << endl;
        cout << "6. Add to an image's pixels green channel" << endl;
        cout << "7. Scale an image's red pixels by 4 and blue by 0" << endl;
        cout << "8. Write 3 new files based off of an image's red, green, and blue pixels" << endl;
        cout << "9. Use an image's red, blue, and green pixels to make a new different image" << endl;
        cout << "10. Roate an image by 180 degrees" << endl;
        cout << "Q to quit\n" << endl;


        cin >> input;

        if (input == "1") {
            //task1 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task1_pixel = read.multiply(image_data_array[6], image_data_array[8],
                                                                             (header_array[6].width *
                                                                              header_array[6].height));
            ofstream outfile_1("./../output/part1.tga", ios::binary);
            read.write_file(header_array[6], task1_pixel, outfile_1);
        } else if (input == "2") {
            //task2 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task2_pixel = read.subtract(image_data_array[1], image_data_array[7],
                                                                             (header_array[7].width *
                                                                              header_array[7].height));
            ofstream outfile_2("./../output/part2.tga", ios::binary);
            read.write_file(header_array[1], task2_pixel, outfile_2);
        } else if (input == "3") {
            //task3 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task3_pre_pixel = read.multiply(image_data_array[6],
                                                                                 image_data_array[9],
                                                                                 (header_array[7].width *
                                                                                  header_array[7].height));
            vector<Image_Processing::Image_Data> task3_pixel = read.screen(image_data_array[10], task3_pre_pixel,
                                                                           (header_array[10].width *
                                                                            header_array[10].height));
            ofstream outfile_3("./../output/part3.tga", ios::binary);
            read.write_file(header_array[10], task3_pixel, outfile_3);
        } else if (input == "4") {
            //task4 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task4_pre_pixel = read.multiply(image_data_array[7],
                                                                                 image_data_array[2],
                                                                                 (header_array[7].width *
                                                                                  header_array[7].height));
            vector<Image_Processing::Image_Data> task4_pixel = read.subtract(task4_pre_pixel, image_data_array[9],
                                                                             (header_array[9].width *
                                                                              header_array[9].height));
            ofstream outfile_4("./../output/part4.tga", ios::binary);
            read.write_file(header_array[9], task4_pixel, outfile_4);
        } else if (input == "5") {
            //task5 ------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task5_pixel = read.overlay(image_data_array[6], image_data_array[8],
                                                                            (header_array[6].width *
                                                                             header_array[6].height));
            ofstream outfile_5("./../output/part5.tga", ios::binary);
            read.write_file(header_array[6], task5_pixel, outfile_5);
        } else if (input == "6") {
            //task6 //task7 ----------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task6_pixel = read.addition(image_data_array[1],
                                                                             (header_array[1].width *
                                                                              header_array[1].height));
            ofstream outfile_6("./../output/part6.tga", ios::binary);
            read.write_file(header_array[1], task6_pixel, outfile_6);
        } else if (input == "7") {
            //task7 --------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> scale;

            int blue;
            int green;
            int red;

            int new_blue = 0;
            int new_green = 1;
            int new_red = 4;

            int new_new_blue;
            int new_new_green;
            int new_new_red;

            for (int i = 0; i < image_data_array[1].size(); ++i) {
                Image_Processing::Image_Data to_scale;
                blue = (int) (image_data_array[1][i].blue);
                green = (int) (image_data_array[1][i].green);
                red = (int) (image_data_array[1][i].red);

                new_new_blue = (blue * new_blue);
                new_new_green = (green * new_green);
                new_new_red = (red * new_red);

                //clamp
                //BLUE ---------------------------------------------------------------------------
                if (new_new_blue < 0) {
                    new_new_blue = 0;
                }
                if (new_new_blue > 255) {
                    new_new_blue = 255;
                }

                //GREEN ---------------------------------------------------------------------------
                if (new_new_green < 0) {
                    new_new_green = 0;
                }

                if (new_new_green > 255) {
                    new_new_green = 255;
                }

                //RED ---------------------------------------------------------------------------
                if (new_new_red < 0) {
                    new_new_red = 0;
                }

                if (new_new_red > 255) {
                    new_new_red = 255;
                }

                to_scale.blue = (unsigned char) (new_new_blue);
                to_scale.green = (unsigned char) (new_new_green);
                to_scale.red = (unsigned char) (new_new_red);
                scale.push_back(to_scale);
            }

            ofstream outfile_7("./../output/part7.tga", ios::binary);

            read.write_file(header_array[1], scale, outfile_7);
        } else if (input == "8") {
            //task 8 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> channel_array_blue;
            vector<Image_Processing::Image_Data> channel_array_green;
            vector<Image_Processing::Image_Data> channel_array_red;

            int orig_blue;
            int orig_green;
            int orig_red;

            for (int i = 0; i < image_data_array[1].size(); ++i) {

                orig_blue = (int) image_data_array[1][i].blue;
                orig_green = (int) image_data_array[1][i].green;
                orig_red = (int) image_data_array[1][i].red;

                //blue channel
                Image_Processing::Image_Data channel_blue;
                channel_blue.blue = (unsigned char) orig_blue;
                channel_blue.green = (unsigned char) orig_blue;
                channel_blue.red = (unsigned char) orig_blue;
                channel_array_blue.push_back(channel_blue);

                //green channel
                Image_Processing::Image_Data channel_green;
                channel_green.blue = (unsigned char) orig_green;
                channel_green.green = (unsigned char) orig_green;
                channel_green.red = (unsigned char) orig_green;
                channel_array_green.push_back(channel_green);

                //red channel
                Image_Processing::Image_Data channel_red;
                channel_red.blue = (unsigned char) orig_red;
                channel_red.green = (unsigned char) orig_red;
                channel_red.red = (unsigned char) orig_red;
                channel_array_red.push_back(channel_red);
            }

            //part a
            ofstream outfile_8_a("./../output/part8_b.tga", ios::binary);
            read.write_file(header_array[1], channel_array_blue, outfile_8_a);
            //part b
            ofstream outfile_8_b("./../output/part8_g.tga", ios::binary);
            read.write_file(header_array[1], channel_array_green, outfile_8_b);
            //part c
            ofstream outfile_8_c("./../output/part8_r.tga", ios::binary);
            read.write_file(header_array[1], channel_array_red, outfile_8_c);
        } else if (input == "9") {
            //task 9 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            vector<Image_Processing::Image_Data> task9;

            vector<int> task9_blue;
            vector<int> task9_green;
            vector<int> task9_red;

            int the_orig_blue;
            int the_orig_green;
            int the_orig_red;

            //blue
            for (int i = 0; i < image_data_array[3].size(); ++i) {
                the_orig_blue = (int) image_data_array[3][i].blue;
                task9_blue.push_back(the_orig_blue);
            }

            //green
            for (int i = 0; i < image_data_array[4].size(); ++i) {
                the_orig_green = (int) image_data_array[4][i].green;
                task9_green.push_back(the_orig_green);

            }

            //red
            for (int i = 0; i < image_data_array[5].size(); ++i) {
                the_orig_red = (int) image_data_array[5][i].red;
                task9_red.push_back(the_orig_red);
            }

            for (int i = 0; i < image_data_array[3].size(); ++i) {
                Image_Processing::Image_Data new_colors;
                new_colors.blue = (unsigned char) task9_blue[i];
                new_colors.green = (unsigned char) task9_green[i];
                new_colors.red = (unsigned char) task9_red[i];

                task9.push_back(new_colors);

            }
            ofstream outfile_9("./../output/part9.tga", ios::binary);
            read.write_file(header_array[5], task9, outfile_9);

        } else if (input == "10") {
            //task 10 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            ofstream outfile_10("./../output/part10.tga", ios::binary);
            outfile_10.write(&header_array[0].idLength, sizeof(header_array[0].idLength));
            outfile_10.write(&header_array[0].colorMapType, sizeof(header_array[0].colorMapType));
            outfile_10.write(&header_array[0].dataTypeCode, sizeof(header_array[0].dataTypeCode));
            outfile_10.write((char *) &header_array[0].colorMapOrigin, sizeof(header_array[0].colorMapOrigin));
            outfile_10.write((char *) &header_array[0].colorMapLength, sizeof(header_array[0].colorMapLength));
            outfile_10.write(&header_array[0].colorMapDepth, sizeof(header_array[0].colorMapDepth));
            outfile_10.write((char *) &header_array[0].xOrigin, sizeof(header_array[0].xOrigin));
            outfile_10.write((char *) &header_array[0].yOrigin, sizeof(header_array[0].yOrigin));
            outfile_10.write((char *) &header_array[0].width, sizeof(header_array[0].width));
            outfile_10.write((char *) &header_array[0].height, sizeof(header_array[0].height));
            outfile_10.write(&header_array[0].bitsPerPixel, sizeof(header_array[0].bitsPerPixel));
            outfile_10.write(&header_array[0].imageDescriptor, sizeof(header_array[0].imageDescriptor));

            for (size_t i = image_data_array[0].size(); i > 0; --i) {
                Image_Processing::Image_Data &pixel = image_data_array[0][i - 1];
                outfile_10.write((char *) (&pixel.blue), sizeof(pixel.blue));
                outfile_10.write((char *) (&pixel.green), sizeof(pixel.green));
                outfile_10.write((char *) (&pixel.red), sizeof(pixel.red));
            }
        }
        else if(input == "Q"){
            break;
        }
        else {
            cout << "Invalid input...\n" << endl;
            continue;
        }
        tasks += input + ",";
        string result = tasks.substr(0, tasks.size() - 1);

        cout << "\n" << "Tasks completed:" << result << "\n" << endl;

    }

    cout << "To see your images, check your output folder!" << endl;
    return 0;
}