# 3D-Viewer-on-C-QT

## Implementation of 3D Viewer.

A program to visualise 3D wireframe models.

## Usage :

- To install the app run `make install`
- To open app run `make open`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`
- To uninstall the app run `make uninstall`

### Overview of "3D Viewer" functions

| Options                                    | Option  description                                                                                                                |
|--------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------|
| Rotate                                     | Clockwise rotation matrix in uniform two-dimensional coordinates                                                                   |
| Translate                                  | Translation matrix in uniform two-dimensional coordinates                                                                          |
| Scale                                      | Scaling matrix in uniform two-dimensional coordinates                                                                              |
| Set projection type                        | Customizing the type of projection (parallel and central)                                                                          |
| Set vertex type and width                  | Customizing display method (none, circle, square) and size of the vertices                                                         |
| Set edges type and width                   | Customizing the type (solid, dashed) and thickness of the edges                                                                    |
| Set color for background, vertex and edges | Customizing the background color, color of vertices and edges                                                                      |
| Screenshot                                 | Saving the captured (rendered) images as bmp and jpeg files                                                                        |
| Record a GIF                               | Recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation |