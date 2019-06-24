#include<iostream>

using namespace std;

class Image{
	int *img;
	int mx;
	int my;
	public:
		Image *init(int tmx, int tmy){
			tmx=0;
			tmy=0;
		}
		
		void set_point(Image *ing, int x, int y, int color){
			mx = x;
			img = &mx;
			my = y;
			img = &my;
			img = &color;
			/*img->mx = x;
			img->my = y;
			img->color = color*/
		}
			
		int get_point(Image *img, int x, int y){
			return img->mx;
			return img->my;
		}
};

int main(){
	return 0;
}
