#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// Constants for safety thresholds
#define COLLISION_THRESHOLD_KM 5.0    // Minimum safe distance (5 km)
#define WARNING_THRESHOLD_KM 10.0     // Warning distance (10 km)
#define TIME_STEP_SEC 1.0             // Time interval (1 second)
#define SIMULATION_TIME_SEC 300.0     // 5 minutes simulation
#define MAX_AIRCRAFT 10

// 3D Vector structure
typedef struct {
    double x, y, z;  // x: longitude, y: latitude, z: altitude (km)
} Vector3D;

// Aircraft structure
typedef struct {
    char callsign[10];      // Aircraft identifier (e.g., "AA101")
    Vector3D position;      // Current position in 3D space (km)
    Vector3D velocity;      // Velocity vector (km/s)
    bool is_active;         // Aircraft status
} Aircraft;

// Function prototypes
double calculate_distance(Vector3D pos1, Vector3D pos2);
Vector3D predict_position(Aircraft aircraft, double time);
bool check_collision_risk(Aircraft aircraft1, Aircraft aircraft2, double time_horizon);
void print_aircraft_status(Aircraft aircraft);
void print_warning(Aircraft aircraft1, Aircraft aircraft2, double distance, double time);
void simulate_traffic(Aircraft* aircraft_list, int num_aircraft);

// Calculate 3D Euclidean distance between two positions
double calculate_distance(Vector3D pos1, Vector3D pos2) {
    double dx = pos1.x - pos2.x;
    double dy = pos1.y - pos2.y;
    double dz = pos1.z - pos2.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// Predict aircraft position after given time
Vector3D predict_position(Aircraft aircraft, double time) {
    Vector3D future_pos;
    future_pos.x = aircraft.position.x + aircraft.velocity.x * time;
    future_pos.y = aircraft.position.y + aircraft.velocity.y * time;
    future_pos.z = aircraft.position.z + aircraft.velocity.z * time;
    return future_pos;
}

// Check if two aircraft will have collision risk within time horizon
bool check_collision_risk(Aircraft aircraft1, Aircraft aircraft2, double time_horizon) {
    double min_distance = INFINITY;
    double critical_time = 0;
    
    // Check distance at multiple time intervals
    for (double t = 0; t <= time_horizon; t += TIME_STEP_SEC) {
        Vector3D pos1 = predict_position(aircraft1, t);
        Vector3D pos2 = predict_position(aircraft2, t);
        double distance = calculate_distance(pos1, pos2);
        
        if (distance < min_distance) {
            min_distance = distance;
            critical_time = t;
        }
        
        // Immediate collision warning
        if (distance <= COLLISION_THRESHOLD_KM) {
            print_warning(aircraft1, aircraft2, distance, t);
            return true;
        }
    }
    
    // Check if aircraft will come dangerously close
    if (min_distance <= WARNING_THRESHOLD_KM) {
        printf("⚠️  WARNING: Aircraft %s and %s will be %.2f km apart at T+%.0f seconds\n",
               aircraft1.callsign, aircraft2.callsign, min_distance, critical_time);
        return true;
    }
    
    return false;
}

// Print collision warning
void print_warning(Aircraft aircraft1, Aircraft aircraft2, double distance, double time) {
    printf("\n🚨 COLLISION ALERT! 🚨\n");
    printf("Aircraft: %s and %s\n", aircraft1.callsign, aircraft2.callsign);
    printf("Distance: %.2f km (CRITICAL - Below %.1f km threshold)\n", 
           distance, COLLISION_THRESHOLD_KM);
    printf("Time to collision: %.0f seconds\n", time);
    printf("IMMEDIATE EVASIVE ACTION REQUIRED!\n");
    printf("----------------------------------------\n");
}

// Print aircraft status
void print_aircraft_status(Aircraft aircraft) {
    printf("Aircraft: %s\n", aircraft.callsign);
    printf("  Position: (%.2f, %.2f, %.2f) km\n", 
           aircraft.position.x, aircraft.position.y, aircraft.position.z);
    printf("  Velocity: (%.3f, %.3f, %.3f) km/s\n", 
           aircraft.velocity.x, aircraft.velocity.y, aircraft.velocity.z);
    printf("  Speed: %.2f km/s (%.0f km/h)\n", 
           sqrt(aircraft.velocity.x*aircraft.velocity.x + 
                aircraft.velocity.y*aircraft.velocity.y + 
                aircraft.velocity.z*aircraft.velocity.z),
           sqrt(aircraft.velocity.x*aircraft.velocity.x + 
                aircraft.velocity.y*aircraft.velocity.y + 
                aircraft.velocity.z*aircraft.velocity.z) * 3600);
}

// Main simulation function
void simulate_traffic(Aircraft* aircraft_list, int num_aircraft) {
    printf("=== AIR TRAFFIC COLLISION DETECTION SYSTEM ===\n\n");
    printf("Safety Parameters:\n");
    printf("- Collision Threshold: %.1f km\n", COLLISION_THRESHOLD_KM);
    printf("- Warning Threshold: %.1f km\n", WARNING_THRESHOLD_KM);
    printf("- Simulation Time: %.0f seconds\n", SIMULATION_TIME_SEC);
    printf("- Time Step: %.1f seconds\n\n", TIME_STEP_SEC);
    
    // Display initial aircraft status
    printf("Initial Aircraft Status:\n");
    printf("------------------------\n");
    for (int i = 0; i < num_aircraft; i++) {
        if (aircraft_list[i].is_active) {
            print_aircraft_status(aircraft_list[i]);
            printf("\n");
        }
    }
    
    // Check all aircraft pairs for collision risk
    printf("Collision Analysis:\n");
    printf("-------------------\n");
    bool any_risk = false;
    
    for (int i = 0; i < num_aircraft; i++) {
        for (int j = i + 1; j < num_aircraft; j++) {
            if (aircraft_list[i].is_active && aircraft_list[j].is_active) {
                if (check_collision_risk(aircraft_list[i], aircraft_list[j], SIMULATION_TIME_SEC)) {
                    any_risk = true;
                }
            }
        }
    }
    
    if (!any_risk) {
        printf("✅ All aircraft maintain safe separation distances.\n");
        printf("No collision risks detected in the next %.0f seconds.\n", SIMULATION_TIME_SEC);
    }
}

int main() {
    // Initialize aircraft array
    Aircraft aircraft_list[MAX_AIRCRAFT];
    int num_aircraft = 4;
    
    // Aircraft 1: Commercial flight heading east
    strcpy(aircraft_list[0].callsign, "AA101");
    aircraft_list[0].position = (Vector3D){0.0, 0.0, 10.0};      // Starting at origin, 10km altitude
    aircraft_list[0].velocity = (Vector3D){0.25, 0.0, 0.0};     // 900 km/h eastbound
    aircraft_list[0].is_active = true;
    
    // Aircraft 2: Regional flight heading north - COLLISION COURSE!
    strcpy(aircraft_list[1].callsign, "DL205");
    aircraft_list[1].position = (Vector3D){15.0, -20.0, 10.0};  // 15km east, 20km south
    aircraft_list[1].velocity = (Vector3D){-0.15, 0.22, 0.0};   // Northwest trajectory
    aircraft_list[1].is_active = true;
    
    // Aircraft 3: Safe flight at different altitude
    strcpy(aircraft_list[2].callsign, "UA312");
    aircraft_list[2].position = (Vector3D){5.0, 5.0, 8.0};      // Different position and altitude
    aircraft_list[2].velocity = (Vector3D){0.20, -0.10, 0.01};  // Southeast, slight climb
    aircraft_list[2].is_active = true;
    
    // Aircraft 4: High altitude flight (safe)
    strcpy(aircraft_list[3].callsign, "BA747");
    aircraft_list[3].position = (Vector3D){-10.0, 10.0, 15.0};  // Higher altitude
    aircraft_list[3].velocity = (Vector3D){0.28, 0.05, 0.0};    // Fast eastbound
    aircraft_list[3].is_active = true;
    
    // Run collision detection simulation
    simulate_traffic(aircraft_list, num_aircraft);
    
    // Demonstrate real-time monitoring capability
    printf("\n=== REAL-TIME MONITORING EXAMPLE ===\n");
    printf("Simulating live tracking for first 30 seconds:\n\n");
    
    for (double t = 0; t <= 30; t += 5) {
        printf("T+%.0f seconds:\n", t);
        Vector3D pos1 = predict_position(aircraft_list[0], t);
        Vector3D pos2 = predict_position(aircraft_list[1], t);
        double distance = calculate_distance(pos1, pos2);
        
        printf("  %s position: (%.2f, %.2f, %.2f)\n", 
               aircraft_list[0].callsign, pos1.x, pos1.y, pos1.z);
        printf("  %s position: (%.2f, %.2f, %.2f)\n", 
               aircraft_list[1].callsign, pos2.x, pos2.y, pos2.z);
        printf("  Separation: %.2f km %s\n", distance, 
               distance < WARNING_THRESHOLD_KM ? "⚠️  WARNING" : "✅ SAFE");
        printf("\n");
    }
    
    return 0;
}