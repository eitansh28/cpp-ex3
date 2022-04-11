//  * AUTHORS: <Eitan Shenkolevski>
//  * 
//  * Date: 2021-04
//  */
#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;
using namespace std;


TEST_CASE("constructor") {
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> identity2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
    vector<double> identity3 = {2, 0, 0};
    Matrix a{identity,3,3};
    Matrix b{identity,3,3};
    Matrix c{identity2,3,3};
    CHECK_THROWS(Matrix d(identity2,3,7));
    CHECK_THROWS(Matrix d(identity2,5,3));
    CHECK_NOTHROW(Matrix d(identity2,3,3));
    CHECK_NOTHROW(Matrix e(identity3,3,1));
}

TEST_CASE("plus & minus") {
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> identity2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
    vector<double> identity3 = {2, 0, 0};
    vector<double> identity4 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
    vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix a{identity,3,3};
    Matrix b{identity2,3,3};
    Matrix c{identity3,1,3};
    Matrix d{identity4,3,3};
    Matrix zeroMat{zero,3,3};
    Matrix e=a-b;
    Matrix aa=a+a;
    CHECK((a!=b));
    CHECK((e==d));
    CHECK((aa==b));
    CHECK_FALSE((aa!=b));
    Matrix minD=-d;
    CHECK((a==minD));
    a-=a;
    CHECK((a==zeroMat));
    CHECK_THROWS(a-c);
    CHECK_THROWS(a+c);
    b+=d;
    b+=d;
    CHECK((b==zeroMat));
    Matrix plusD=+d;
    CHECK((d==plusD));
}

TEST_CASE("compare") {
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> identity2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
    vector<double> identity3 = {2, 0, 0};
    vector<double> identity4 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
    vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix a{identity,3,3};
    Matrix b{identity2,3,3};
    Matrix c{identity3,1,3};
    Matrix d{identity4,3,3};
    Matrix zeroMat{zero,3,3};
    CHECK((a!=b));
    CHECK((a!=d));
    CHECK((a>d));
    CHECK((a<b));
    CHECK_THROWS(bool ans=(a!=c));
    CHECK_THROWS(bool ans=(a>c));
}

TEST_CASE("mult"){
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> identity2 = {2, 0, 0, 0, 2, 0, 0, 0, 2};
    vector<double> identity3 = {2, 0, 0};
    vector<double> identity4 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
    vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix a{identity,3,3};
    Matrix b{identity2,3,3};
    Matrix c{identity3,1,3};
    Matrix d{identity4,3,3};
    Matrix zeroMat{zero,3,3};
    a*=2;
    CHECK((a==b));
    a*=(-0.5);
    CHECK((a==d));
    Matrix e=(-2*d);
    CHECK((e==b));
    vector<double> arr2 = {3, 1, 4, 5, 2, 0};
    vector<double> arr3 = {3, 2, 0, 8, 3, 0};
    vector<double> arr4 = {17, 9, 0 ,52, 23 ,0 ,6, 4, 0};
    Matrix f{arr2, 3, 2};
    Matrix g{arr3, 2, 3};
    Matrix dmulte(arr4, 3, 3);
    CHECK(((f*g)==dmulte));

}