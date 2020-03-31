#ifndef VISUALIZATION_VISUALIZATION_WINDOW_H
#define VISUALIZATION_VISUALIZATION_WINDOW_H


#include "visualization/transformations.h"

typedef struct VisualizationWindow {
  LogicalScreenGeometry geometry;

  SDL_Window* window;
  SDL_Renderer* renderer;

  int initalized;

} VisualizationWindow;


/**
 * @brief Initalizes a visualization window
 * @param window The window to initalize
 * @param title The title of the window
 * @return 0 on success
 */
int initalizeVisualizationWindow(VisualizationWindow* window,
                                  const char* title);

/**
 * @brief Destroys a visualization window
 * @param window The window to destroy
 */
void destroyVisualizationWindow(VisualizationWindow* window);

/**
 * @brief Render the VisualizationWindow
 * @param window The window to render
 */
void renderVisualizationWindow(VisualizationWindow* window);

/**
 * @brief Clear the VisualizationWindow
 * @param window The window to clear
 */
void clearVisualizationWindow(VisualizationWindow* window);


/**
 * @brief Set the drawing color on a window
 * @param window The window to change
 * @param color The new color, each component in [0, 1]
 */
void setColor(VisualizationWindow* window, const vector3f* color);

#endif

