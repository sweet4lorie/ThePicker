#include "Mat4.h"
#include "Vec3.h"

Mat4::Mat4() {

	//Set the Identity Matrix
	//row
	for (int i = 0; i < 4; ++i){
		//column
		for (int j = 0; j < 4; ++j){
			//check to see if column and row are the same
			_m[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
		}

	}
}

Mat4::Mat4(const float m[16]){

	for (int i = 0; i < 16; ++i){

		_m[i] = m[i];
	}
}

Mat4::Mat4(const float s){

	for (int i = 0; i < 16; ++i){

		_m[i] = s;
	}
}

Mat4::Mat4(const Mat4& m){

	for (int i = 0; i < 16; ++i){

		_m[i] = m._m[i];
	}
}

Mat4& Mat4::operator= (const Mat4& rhs){

	if (this == &rhs){

		return *this;
	}

	for (int i = 0; i < 16; ++i)
		_m[i] = rhs._m[i];

	return *this;
}



Mat4 Mat4::operator+ (const Mat4& other) const{

	Mat4 sum;

	for (int i = 0; i < 16; ++i)
		sum._m[i] = _m[i] + other._m[i];

	return sum;
}
Mat4 Mat4::operator+ (const float other[16]) const{

	Mat4 sum;
	for (int i = 0; i < 16; ++i)
		sum._m[i] = _m[i] + other[i];

	return sum;
}

Mat4 Mat4::operator- (const Mat4& other) const{

	Mat4 sum;

	for (int i = 0; i < 16; ++i)
		sum._m[i] = _m[i] - other._m[i];

	return sum;
}
Mat4 Mat4::operator- (const float other[16]) const{
	Mat4 sum;
	for (int i = 0; i < 16; ++i)
		sum._m[i] = _m[i] - other[i];

	return sum;
}

Mat4 Mat4::operator* (const Mat4& other) const{

	Mat4 mult;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mult._m[j * 4 + i] = 0;
			for (int k = 0; k < 4; k++) {
				mult._m[j * 4 + i] += _m[k * 4 + i] * other._m[j * 4 + k];
			}
		}
	}
	return mult;
}

Mat4 Mat4::operator* (const float other[16]) const{

	Mat4 mult;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mult._m[j * 4 + i] = 0;

			for (int k = 0; k < 4; k++) {
				mult._m[j * 4 + i] += _m[k * 4 + i] * other[j * 4 + k];
			}
		}
	}
	return mult;

}

Mat4 Mat4::operator* (const float & s) const{
	Mat4 mult;

	for (int i = 0; i < 16; ++i)
		mult._m[i] = _m[i] * s;

	return mult;
}
Mat4 Mat4::operator/ (const float & s) const{

	Mat4 div;

	for (int i = 0; i < 16; ++i)
		div._m[i] = _m[i] / s;

	return div;
}

Mat4& Mat4::operator+= (const Mat4& other){

	for (int i = 0; i < 16; ++i)
		_m[i] += other._m[i];

	return *this;

}
Mat4& Mat4::operator+= (const float other[16]){

	for (int i = 0; i < 16; ++i)
		_m[i] += other[i];

	return *this;
}

Mat4& Mat4::operator-= (const Mat4& other){

	for (int i = 0; i < 16; ++i)
		_m[i] -= other._m[i];

	return *this;

}
Mat4& Mat4::operator-= (const float other[16]){

	for (int i = 0; i < 16; ++i)
		_m[i] += other[i];

	return *this;
}

Mat4& Mat4::operator*= (const Mat4& other){

	Mat4 mult;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mult._m[j * 4 + i] = 0;

			for (int k = 0; k < 4; k++) {
				mult._m[j * 4 + i] += _m[k * 4 + i] * other._m[j * 4 + k];
			}
		}
	}
	
	*this = mult;
	return *this;
}
Mat4& Mat4::operator*= (const float other[16]){

	Mat4 mult;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mult._m[j * 4 + i] = 0;

			for (int k = 0; k < 4; k++) {
				mult._m[j * 4 + i] += _m[k * 4 + i] * other[j * 4 + k];
			}
		}
	}

	return *this;
}

Mat4& Mat4::operator*= (const float & s){

	for (int i = 0; i < 16; ++i)
		_m[i] *= s;

	return *this;
}

Mat4& Mat4::operator/= (const float & s){
	for (int i = 0; i < 16; ++i)
		_m[i] /= s;

	return *this;
}

bool Mat4::operator==(const Mat4& other)const{

	
	for (int i = 0; i < 16; ++i){

		if (_m[i] != other._m[i])
			return false;
	}

	return true;
}

bool Mat4::operator== (const float other[16])const{


	for (int i = 0; i < 16; ++i){

		if (_m[i] != other[i])
			return false;
	}
	return true;
}

float& Mat4::operator[](const int & i){

	return _m[i];
}

const float& Mat4::operator[](const int & i) const{

	return _m[i];
}

//Built in Functions
float Mat4::Determinant() const{

	//Get all the 2x2 determinants
	float det_a = _m[10] * _m[15] - _m[11] * _m[14];
	float det_b = _m[9] * _m[15] - _m[11] * _m[13];
	float det_c = _m[9] * _m[14] - _m[10] * _m[13];
	float det_d = _m[8] * _m[15] - _m[11] * _m[12];
	float det_e = _m[8] * _m[14] - _m[10] * _m[12];
	float det_f = _m[9] * _m[15] - _m[11] * _m[13];
	float det_g = _m[8] * _m[13] - _m[9] * _m[12];
	float det_h = _m[9] * _m[14] - _m[10] * _m[13];
	float det_i = _m[8] * _m[14] - _m[10] * _m[12];

	//Then get the 3x3 determinants * multiplied with the cofactor value
	float cof_a =	+_m[0] * (_m[5] * det_a - _m[6] * det_b + _m[7] * det_c);
	float cof_b = -_m[1] * (_m[4] * det_a - _m[6] * det_d + _m[7] * det_e);
	float cof_c = +_m[2] * (_m[4] * det_f - _m[5] * det_d + _m[7] * det_g);
	float cof_d = -_m[3] * (_m[4] * det_h - _m[5] * det_i + _m[6] * det_g);

	//return the sum
	return cof_a + cof_b + cof_c + cof_d;

}

Mat4 Mat4::Get_Inverse() const{

	Mat4 result;

	float det = Determinant();

	if (det != 0){

		//Get cofactors of the matrix;
		float mult = 1.0;
		bool check = true;

		//row
		for (int r = 0; r < 4; ++r){
			//column
			for (int c = 0; c < 4; ++c){
				//change the sign
				check = (c / 3 == 1) ? false : true;
				mult = (check) ? 1.0f : -1.0f;
				//get adjugate
				result._m[r * 4 + c] = mult * Det3x3(Get_Minor_Matrix(r, c));

				//switch sign
				check = !check;
			}
		}

		result /= det;

		return result;
	}
	else{
		std::cerr << "Determinate of matrix is 0";
        return result;
	}
}

void Mat4::Inverse(){
	
	Mat4 result;

	float det = Determinant();

	if (det != 0){

		//Get cofactors of the matrix;
		float mult = 1.0;
		bool check = true;

		//row
		for (int r = 0; r < 4; ++r){
			//column
			for (int c = 0; c < 4; ++c){
				//change the sign
				mult = (check) ? 1.0f : -1.0f;

				//get adjugate
				result._m[r * 4 + c] = mult * Det3x3(Get_Minor_Matrix(r, c));
				
				
				//switch sign
				check = !check;
			}

			std::cout << std::endl;
		}
		result /= det;

		*this = result;
	}
	else{
		std::cerr << "Determinate of matrix is 0";
	}


}

Mat4 Mat4::Get_Transpose() const{

	Mat4 result;

	result._m[0] = _m[0];
	result._m[1] = _m[4];
	result._m[2] = _m[8];
	result._m[3] = _m[12];
	result._m[4] = _m[1];
	result._m[5] = _m[5];
	result._m[6] = _m[9];
	result._m[7] = _m[13];
	result._m[8] = _m[2];
	result._m[9] = _m[6];
	result._m[10] = _m[10];
	result._m[11] = _m[14];
	result._m[12] = _m[3];
	result._m[13] = _m[7];
	result._m[14] = _m[1];
	result._m[15] = _m[15];

	return result;
}

void Mat4::Transpose(){

	float swap;
	swap = _m[1];
	_m[1] = _m[4];
	_m[4] = swap;

	swap = _m[8];
	_m[8] = _m[2];
	_m[2] = swap;

	swap = _m[3];
	_m[3] = _m[12];
	_m[12] = swap;

	swap = _m[9];
	_m[9] = _m[6];
	_m[6] = swap;

	swap = _m[13];
	_m[13] = _m[7];
	_m[7] = swap;

	swap = _m[11];
	_m[11] = _m[14];
	_m[14] = swap;

}

Mat4::~Mat4(){}

float* Mat4::Get_Minor_Matrix(int column, int row) const{

	float* m = new float[9];
	//row
	int i = 0;
	for (int r = 0; r < 4; ++r){
		//column
		
		//our r row is the row value skip
		if (r == row)
			continue;
		for (int c = 0; c < 4; ++c){
			
			//our current c is the column value skip
			if (c == column)
				continue;
			m[i] = _m[r * 4 + c];
			++i;
		}
		//Break out once we got all of the values
	}
	return m;
}

Mat4 Mat4::Translate(const Vec3 & v){

	Mat4 translate;

	translate[12] = v._x;
	translate[13] = v._y;
	translate[14] = v._z;


	return translate;
}

Mat4 Mat4::Translate(const float & x, const float & y, const float & z){

	Mat4 translate;

	translate[12] = x;
	translate[13] = y;
	translate[14] = z;

	return translate;
}

//TODO: FIX ROTATION	static Mat4 Rotate(const Vector3D& angles);

Mat4 Mat4::Scale(const Vec3 & s){

	Mat4 scale;

	scale[0] = s._x;
	scale[5] = s._y;
	scale[10] = s._z;

	return scale;
}

Mat4 Mat4::Scale(const float & s){
	Mat4 scale;

	scale[0] = s;
	scale[5] = s;
	scale[10] = s;

	return scale;

}

Mat4 Mat4::Scale(const float & x, const float & y, const float & z){
	Mat4 scale;

	scale[0] = x;
	scale[5] = y;
	scale[10] = z;

	return scale;

}


std::ostream & operator<<(std::ostream &os, const Mat4& mat){
	os.setf(std::ios_base::fixed, std::ios_base::floatfield);
	return os //<< os.precision(4) 
		<<
		"[ " << mat[0] << ", " << mat[4] << ", " << mat[8] << ", " << mat[12] << "]\n" <<
		"[ " << mat[1] << ", " << mat[5] << ", " << mat[9] << ", " << mat[13] << "]\n" <<
		"[ " << mat[2] << ", " << mat[6] << ", " << mat[10] << ", " << mat[14] << "]\n" <<
		"[ " << mat[3] << ", " << mat[7] << ", " << mat[11] << ", " << mat[15] << "]\n";
}

float Det3x3(const float m[9]){

	return m[0] * (m[4] * m[8] - m[5] * m[7])
  		 - m[1] * (m[3] * m[8] - m[5] * m[6])
		 + m[2] * (m[3] * m[7] - m[4] * m[6]);

}
