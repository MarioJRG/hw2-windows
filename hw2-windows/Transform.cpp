// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
    // YOUR CODE FOR HW1 HERE
    float randianAnglee = degrees * (pi / 180);
    float cosMinusOne = 1 - cos(randianAnglee);
    vec3 norm = glm::normalize(axis);
    mat3 cna;

    mat3 rotationMatriz = (mat3(vec3(cos(randianAnglee) + (pow(norm.x, 2) * cosMinusOne), norm.x * norm.y * cosMinusOne - norm.z * sin(randianAnglee), norm.x * norm.z * cosMinusOne + norm.y * sin(randianAnglee)),
        vec3(norm.y * norm.x * cosMinusOne + norm.z * sin(randianAnglee), cos(randianAnglee) + (pow(norm.y, 2) * cosMinusOne), norm.y * norm.z * cosMinusOne - norm.x * sin(randianAnglee)),
        vec3(norm.z * norm.x * cosMinusOne - norm.y * sin(randianAnglee), norm.z * norm.y * cosMinusOne + norm.x * sin(randianAnglee), cos(randianAnglee) + (pow(norm.z, 2) * cosMinusOne))));

    // You will change this return call
    return glm::transpose(rotationMatriz);
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    mat3 matrizT = rotate(degrees, up);
    eye = eye * matrizT;
    up = up * matrizT;
    //printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    float radian = degrees * (pi / 180);
    vec3 ortogonal = glm::cross(up, eye);
    //mat3 matrizT = mat3(vec3(1, 0, 0),
        //vec3(0, cos(radian), -sin(radian)),
        //vec3(0, sin(radian), cos(radian)));
    mat3 matrizT = rotate(-degrees, ortogonal);
    eye = eye * matrizT;
    up = up * matrizT;
    //vec3 hola = glm::normalize(eye);
    //printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up)
{

    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);


    // You will change this return call
    return glm::transpose(mat4(vec4(u.x, u.y, u.z, glm::dot(u, -eye)),
        vec4(v.x, v.y, v.z, glm::dot(v, -eye)),
        vec4(w.x, w.y, w.z, glm::dot(w, -eye)),
        vec4(0, 0, 0, 1)));


}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    //fovy = fiel of view 
    float angle = glm::radians(fovy) / 2;
    // cotangente theta 
    float d = 1 / tanf(angle);

    float A = -((zFar + zNear) / (zFar - zNear));
    float B = -((2 * zFar * zNear) / (zFar - zNear));
    mat4 ret = mat4(d / aspect, 0, 0, 0,
        0, d, 0, 0,
        0, 0, A,-1 ,
        0, 0, B, 0);
    

    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    //return glm::perspective(fovy,aspect,zNear,zFar);
    return ret;
}

mat4 Transform::scale(const float& sx, const float& sy, const float& sz)
{
    mat4 ret = glm::transpose(mat4(sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1));
    
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    //printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", sx, sy, sz, sqrt(pow(sx, 2) + pow(sy, 2) + pow(sz, 2)));
    return ret;
}

mat4 Transform::translate(const float& tx, const float& ty, const float& tz)
{
    mat4 ret = glm::transpose(mat4(1, 0, 0, tx,
        0, 1, 0, ty,
        0, 0, 1, tz,
        0, 0, 0, 1));
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
   
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3& up, const vec3& zvec)
{
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
