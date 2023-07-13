//
// Created by liusheng on 23Äê7ÔÂ13ÈÕ.
//

#ifndef CODE03_PDF_H
#define CODE03_PDF_H

#include "../../09_Sampling_Lights_Directly/src/rtweekend.h"
#include "../../09_Sampling_Lights_Directly/src/onb.h"


class pdf {
    public:
        pdf(){}
        virtual ~pdf() {}

        virtual  double value(const vec3& direction) const = 0;
        virtual vec3 generate() const = 0;


    public:

};


inline vec3 random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = sqrt(1-r2);

    auto phi = 2*pi*r1;
    auto x = cos(phi)* sqrt(r2);
    auto y = sin(phi)* sqrt(r2);

    return vec3(x, y, z);
}

class cosine_pdf : public pdf {
    public:
        cosine_pdf(const vec3& w) {uvw.build_from_w(w);}
        virtual double value(const vec3& direction) const override {
            auto cosine = dot(unit_vector(direction), uvw.w());
            return (cosine <= 0) ? 0 : cosine/pi;
        }

        virtual vec3 generate() const override {
            return uvw.local(random_cosine_direction());
        }

    public:
        onb uvw;
};



#endif //CODE03_PDF_H
