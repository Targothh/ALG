#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int mat_h, mat_w;
    bool next_sector;
    int x , y , x2, y2;
    int max_border_val = 0;
    scanf("%d %d", &mat_h, &mat_w);
    //nacteni vstupni matice
    vector <vector<int>> in_mat(mat_h, vector<int> (mat_w)); 
    for (int i = 0; i < mat_h; i++) {
        for (int j = 0; j < mat_w; j++) {
            scanf("%d", &in_mat[i][j]);
        }
    }
    // presum pro ->x , ->y i sektoru
    vector <vector<int>> sum_x_mat(mat_h, vector<int> (mat_w+1));
    vector <vector<int>> sum_y_mat(mat_h+1, vector<int> (mat_w));
    vector <vector<int>> sector_map_mat(mat_h, vector<int> (mat_w));
    vector <vector<int>> sector_x_mat(mat_h, vector<int> (mat_w));
    vector <vector<int>> sector_y_mat(mat_h, vector<int> (mat_w));
    vector <vector<int>> prefix_map_mat(mat_h, vector<int> (mat_w));
    for (int i = 0; i < mat_h; i++) {
        for (int j = 0; j < mat_w; j++) {
            if (j == 0){
                sum_x_mat[i][j] = in_mat[i][j];
            } else {
                sum_x_mat[i][j] = sum_x_mat[i][j - 1] + in_mat[i][j];
            }
            if (i == 0){
                sum_y_mat[i][j] = in_mat[i][j];
            } else {
                sum_y_mat[i][j] = sum_y_mat[i - 1][j] + in_mat[i][j];
            }
            if (in_mat[i][j] == 0){
                sector_map_mat[i][j] = 1;
            } else {
                sector_map_mat[i][j] = 0;
            }
            if (j == 0) {
                sector_x_mat[i][j] = sector_map_mat[i][j];
            } else {
                sector_x_mat[i][j] = sector_x_mat[i][j - 1] + sector_map_mat[i][j];
            }
            if (i == 0) {
                sector_y_mat[i][j] = sector_map_mat[i][j];
            } else {
                sector_y_mat[i][j] = sector_y_mat[i - 1][j] + sector_map_mat[i][j];
            }
        }
    }
    for (int i = 0; i < mat_h; i++) { // vypocitani 2D "prefixu" sektoru 
        for (int j = 0; j < mat_w; j++) {
            if (i > 0) {
                prefix_map_mat[i][j] += prefix_map_mat[i - 1][j];
            }
            if (j > 0) {
                prefix_map_mat[i][j] += prefix_map_mat[i][j - 1];
            }
            if (i > 0 && j > 0) {
                prefix_map_mat[i][j] -= prefix_map_mat[i - 1][j - 1];
            }
            if (sector_map_mat[i][j] == 1) {
                if ((i == 0 || sector_map_mat[i - 1][j] == 0) && (j == 0 || sector_map_mat[i][j - 1] == 0)) {
                    prefix_map_mat[i][j] += 1;
                }
            }
        }
    }
    int pico =1;
    int sector_count = prefix_map_mat[mat_h - 1][mat_w - 1];
    for (int i = 0; i < mat_h; i ++) {
        for (int j = 0; j < mat_w; j++) {
            for (int i2 = i + 1; i2 < mat_h; i2 ++) {
                for (int j2 = j + 1; j2 < mat_w; j2++) {
                    //i = 3, j = 0, i2 = 8, j2 = 9;
                    if (j == 0) {
                        if (sector_x_mat[i2][j2] != sector_x_mat[i2][j] || sector_x_mat[i][j2] != sector_x_mat[i][j]) {
                            continue;
                        }
                    } else {
                        if (sector_x_mat[i2][j2] != sector_x_mat[i2][j - 1] || sector_x_mat[i][j2] != sector_x_mat[i][j - 1]) {
                            continue;
                        }
                    }
                    if (i == 0){
                        if (sector_y_mat[i2][j2] != sector_y_mat[i][j2] || sector_y_mat[i2][j] != sector_y_mat[i][j]) {
                            continue;
                        }
                    } else {
                        if (sector_y_mat[i2][j2] != sector_y_mat[i - 1][j2] || sector_y_mat[i2][j] != sector_y_mat[i - 1][j]) {
                            continue;
                        }
                    }

                    int sector_count_a;
                    sector_count_a = prefix_map_mat[i2][j2];
                    
                    if (i > 0) {
                        sector_count_a -= prefix_map_mat[i - 1][j2];
                    }
                    if (j > 0) {
                        sector_count_a -= prefix_map_mat[i2][j - 1];
                    }
                    if (i > 0 && j > 0) {
                        sector_count_a += prefix_map_mat[i - 1][j - 1];
                    }
                    if (sector_count_a != sector_count/2 ) {
                        //cout << "error";
                        continue;
                    }
                    int border_val = 0;
                    border_val += sum_x_mat[i][j2] - sum_x_mat[i][j - 1];
                    border_val += sum_x_mat[i2][j2] - sum_x_mat[i2][j - 1];
                    border_val += sum_y_mat[i2 - 1][j2] - sum_y_mat[i][j2];
                    border_val += sum_y_mat[i2 - 1][j] - sum_y_mat[i][j];
                    if (border_val >= max_border_val){
                        x = j, y = i, x2=j2, y2=i2;
                        max_border_val = border_val;
                    }
                }

            }
        }
    }

    cout << max_border_val << endl;
    return 0;
}