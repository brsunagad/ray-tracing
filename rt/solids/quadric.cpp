#include <rt/solids/quadric.h>

namespace rt {

  
    Quadric::Quadric(const Point& center, const float& A, const float& B, const float& C, const float& D, const float& E, const float& F, const float& G,
        const float& H, const float& I, const float& J, CoordMapper* texMapper, Material* material): A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H),
        I(I), J(J),center(center), Solid(texMapper, material) {}
    

    BBox Quadric::getBounds() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const {
       float ox = ray.o.x - center.x;
       float oy = ray.o.y - center.y;
       float oz = ray.o.z - center.z;
       float dx = ray.d.x;
       float dy = ray.d.y;
       float dz = ray.d.z;
       float t;
       Vector normal;
       float Aq = A * dx * dx + B * dy * dy + C * dz * dz + D * dx * dy + E * dx * dz + F * dy * dz;
       float Bq = 2 * A * ox * dx + 2 * B * oy * dy + 2 * C * oz * dz + E * (ox * dz + dx * oz) + D * (ox * dy + dx * oy) + F * (oy * dz + dy * oz) + G * dx + H * dy + I * dz;
       float Cq = A * ox * 2 + B * oy * 2 + C * oz * 2 + D * ox * oy + E * ox * oz + F * oy * oz + G * ox + H * oy + I * oz + J;

       if (Aq < epsilon && Aq > -epsilon) {
           t = -Cq / Bq;
           if ((t > epsilon) && (t < previousBestDistance)) {
               Point hit = ray.getPoint(t);
               normal = Vector(2 * A * hit.x + D * hit.y + E * hit.z + G, 2 * B * hit.y + D * hit.x + F * hit.z + H, 2 * C * hit.z + E * hit.x + F * hit.y + I).normalize();
               if (dot(normal, ray.d) > 0) {
                   normal = -normal;
               }
               return Intersection(t, ray, this, normal, hit);
           }
       }

       if ((Aq < epsilon) || (Aq>epsilon)) {
           if ((Bq * Bq - 4 * Aq * Cq) < 0.0f) {
               return  Intersection::failure();
           }
           else {
               t = (-Bq - (sqrt(Bq * Bq - 4 * Aq * Cq))) / (2 * Aq);
               if ((t > epsilon) && (t < previousBestDistance)) {
                   Point hit = ray.getPoint(t);
                   normal = Vector(2 * A * hit.x + D * hit.y + E * hit.z + G, 2 * B * hit.y + D * hit.x + F * hit.z + H, 2 * C * hit.z + E * hit.x + F * hit.y + I).normalize();
                   if (dot(normal, ray.d) > 0) {
                       normal = -normal;
                   }
                   return Intersection(t, ray, this, normal, hit);
               }
               t = (-Bq + (sqrt(Bq * Bq - 4 * Aq * Cq))) / (2 * Aq);
               if ((t > epsilon) && (t < previousBestDistance)) {
                   Point hit = ray.getPoint(t);
                   normal = Vector(2 * A * hit.x + D * hit.y + E * hit.z + G, 2 * B * hit.y + D * hit.x + F * hit.z + H, 2 * C * hit.z + E * hit.x + F * hit.y + I).normalize();
                   if (dot(normal, ray.d) > 0) {
                       normal = -normal;
                   }
                   return Intersection(t, ray, this, normal, hit);
               }
           }
       }
       return  Intersection::failure();
    }

    Solid::Sample Quadric::sample() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

    float Quadric::getArea() const {
        /* TODO */ NOT_IMPLEMENTED;
    }

}