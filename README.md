# 2D Gravity Simulation

A real-time 2D gravitational physics simulation written in C using Raylib. The simulation demonstrates orbital mechanics with both unequal mass systems (planet-star) and equal mass binary systems.

## Features

- Real-time gravitational force calculations using Newton's law of universal gravitation
- Support for both unequal mass orbits (planet around star) and equal mass binary systems
- Automatic orbital velocity calculations for circular orbits
- Toroidal space wrapping to keep objects on screen
- 60 FPS smooth animation
- Configurable mass ratios and gravitational constants

## Physics Implementation

The simulation uses:
- **Force calculation**: F = G * m1 * m2 / r²
- **Orbital velocity**: v = √(GM/r) for circular orbits
- **Binary systems**: Each mass orbits around the other with velocity v = √(GM_other/r)
- **Euler integration**: Simple but effective for real-time simulation

## Controls

The simulation runs automatically. Masses will orbit based on their initial conditions and mass ratios.

## Configuration

Key parameters in the code:
- `G`: Gravitational constant (default: 80000 - scaled for visual appeal)
- Mass ratios: Equal masses create binary systems, unequal masses create planet-star systems
- Initial positions and velocities are automatically calculated for circular orbits

## Building and Running

### Prerequisites
- GCC compiler
- Raylib library

### Compilation
```bash
gcc -o gravity_sim main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Running
```bash
./gravity_sim
```

## Technical Details

- **Resolution**: 1920x1080
- **Frame rate**: 60 FPS
- **Integration method**: Euler method with adaptive timestep
- **Boundary conditions**: Toroidal topology (wraparound edges)

The simulation automatically calculates proper orbital velocities based on the empirically-derived relationship: `v = 447 * sqrt(400/distance)` for the given gravitational constant.

## Future Improvements

- 3D implementation with camera controls
- Multiple body systems (N-body problem)
- Different integration methods (Runge-Kutta, Verlet)
- Orbital trail rendering
- Energy and momentum conservation analysis

## Physics Background

This simulation demonstrates classical Newtonian mechanics in action. The orbital dynamics follow Kepler's laws, and the system conserves angular momentum (though energy may drift slightly due to numerical integration errors).

## License

Open source - feel free to modify and experiment with the physics parameters.
