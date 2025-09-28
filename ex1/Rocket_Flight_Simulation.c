#include <stdio.h>
#include <math.h>

#define G 9.81  // graviteti (m/s^2)
#define RHO 1.225 // densiteti i ajrit (kg/m^3)
#define DT 0.1 // hapi kohor (sekonda)

int main() {
    // Parametrat fillestarë
    double mass = 500.0;        // kg (raketa + karburanti)
    double fuel_mass = 300.0;   // kg
    double burn_rate = 2.0;     // kg/s
    double thrust = 8000.0;     // N (forca e motorit)
    double area = 1.0;          // m^2 (sipërfaqja frontale)
    double drag_coeff = 0.5;    // koeficienti i rezistencës

    double altitude = 0.0;
    double velocity = 0.0;
    double time = 0.0;

    printf("Time(s)\tAlt(m)\tVel(m/s)\tMass(kg)\n");
    printf("-------------------------------------------------\n");

    while (altitude >= 0) {
        // nëse ka karburant, llogarit thrust, përndryshe thrust = 0
        if (fuel_mass > 0) {
            fuel_mass -= burn_rate * DT;
            if (fuel_mass < 0) fuel_mass = 0;
        } else {
            thrust = 0;
        }

        mass = 200.0 + fuel_mass; // masa totale (200 kg struktura)

        // forcat
        double weight = mass * G;
        double drag = 0.5 * RHO * drag_coeff * area * velocity * velocity;

        // drejtimi i drag është kundër lëvizjes
        if (velocity < 0) drag = -drag;

        // akselerimi neto
        double accel = (thrust - weight - drag) / mass;

        // përditëso shpejtësinë dhe lartësinë
        velocity += accel * DT;
        altitude += velocity * DT;
        time += DT;

        // printo rezultatet çdo 1 sekondë
        if (fmod(time, 1.0) < 0.0001)
            printf("%.1f\t%.2f\t%.2f\t%.2f\n", time, altitude, velocity, mass);

        // ndalo kur raketa bie përsëri në tokë
        if (altitude < 0 && time > 2) break;
    }

    printf("\nSimulation finished at t=%.1fs, altitude=%.2fm\n", time, altitude);

    return 0;
}
