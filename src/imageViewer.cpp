#include "imageViewer.h"
#include "def.h"
#include "sdlutils.h"

#define IMAGEVIEWER_SCROLL_SPEED      20

//------------------------------------------------------------------------------

// Supported extensions
bool ImageViewer::extensionIsSupported(const std::string &p_ext)
{
   return p_ext == "jpg" || p_ext == "jpeg" || p_ext == "png" || p_ext == "ico" || p_ext == "bmp";
}

//------------------------------------------------------------------------------

// Constructor
ImageViewer::ImageViewer(const std::string &p_title):
   IWindow(true, p_title),
   m_image(NULL),
   m_imageW(0),
   m_imageH(0),
   m_fitToScreen(true)
{
   // Load image
   m_image = SDLUtils::loadTexture(p_title);
   if (m_image != NULL)
      SDL_QueryTexture(m_image, NULL, NULL, &m_imageW, &m_imageH);
}

//------------------------------------------------------------------------------

// Destructor
ImageViewer::~ImageViewer(void)
{
   if (m_image != NULL)
   {
      SDL_DestroyTexture(m_image);
      m_image = NULL;
   }
}

//------------------------------------------------------------------------------

// Draw window
void ImageViewer::render(const bool p_focus)
{
   // Clear screen
   SDL_SetRenderDrawColor(g_renderer, COLOR_BODY_BG, 255);
   SDL_RenderClear(g_renderer);

   // Render title background
   SDL_SetRenderDrawColor(g_renderer, COLOR_TITLE_BG, 255);
   SDL_Rect rect { 0, 0, SCREEN_WIDTH, LINE_HEIGHT };
   SDL_RenderFillRect(g_renderer, &rect);

   // Render title
   SDLUtils::renderTexture(g_iconFile, MARGIN_X, LINE_HEIGHT / 2, SDLUtils::T_ALIGN_LEFT, SDLUtils::T_ALIGN_MIDDLE);
   SDLUtils::renderText(m_title, MARGIN_X + ICON_SIZE + MARGIN_X, LINE_HEIGHT / 2, {COLOR_TEXT_NORMAL}, {COLOR_TITLE_BG}, SDLUtils::T_ALIGN_LEFT, SDLUtils::T_ALIGN_MIDDLE);

   // Error case
   if (m_image == NULL)
   {
      SDLUtils::renderText("Unable to load image", SCREEN_WIDTH / 2, (SCREEN_HEIGHT + LINE_HEIGHT) / 2, {COLOR_TEXT_NORMAL}, {COLOR_BODY_BG}, SDLUtils::T_ALIGN_CENTER, SDLUtils::T_ALIGN_MIDDLE);
      return;
   }

   if (m_fitToScreen && (m_imageW > SCREEN_WIDTH || m_imageH > SCREEN_HEIGHT - LINE_HEIGHT))
   {
      // Resize image to fit the screen
      double aspectRatioScreen = static_cast<double>(SCREEN_WIDTH) / (SCREEN_HEIGHT - LINE_HEIGHT);
      double aspectRatioImage = static_cast<double>(m_imageW) / m_imageH;
      double resizeFactor = 0.0;
      if (aspectRatioImage > aspectRatioScreen)
         resizeFactor = static_cast<double>(m_imageW) / SCREEN_WIDTH;
      else
         resizeFactor = static_cast<double>(m_imageH) / (SCREEN_HEIGHT - LINE_HEIGHT);
      int imageFitW = static_cast<double>(m_imageW) / resizeFactor;
      int imageFitH = static_cast<double>(m_imageH) / resizeFactor;
      SDL_Rect destRect = { (SCREEN_WIDTH - imageFitW) / 2, LINE_HEIGHT + ((SCREEN_HEIGHT - LINE_HEIGHT - imageFitH) / 2), imageFitW, imageFitH };
      SDL_RenderCopy(g_renderer, m_image, NULL, &destRect);
   }
   else
   {
      // Display image as it is
      SDLUtils::renderTexture(m_image, (m_imageW > SCREEN_WIDTH ? m_camera.x : 0) + (SCREEN_WIDTH / 2), (m_imageH > SCREEN_HEIGHT - LINE_HEIGHT ? m_camera.y : 0) + ((SCREEN_HEIGHT + LINE_HEIGHT) / 2), SDLUtils::T_ALIGN_CENTER, SDLUtils::T_ALIGN_MIDDLE);
   }
}

//------------------------------------------------------------------------------

// Key pressed
void ImageViewer::keyPressed(const SDL_Event &event)
{
   // Button Validate : change original / fit
   if (BUTTON_PRESSED_VALIDATE)
   {
      // Reset timer
      resetTimer();
      // Change original / fit
      m_fitToScreen = ! m_fitToScreen;
      m_camera.x = 0;
      m_camera.y = 0;
      g_hasChanged = true;
      return;
   }
   // Button Back
   if (BUTTON_PRESSED_BACK)
   {
      // Reset timer
      resetTimer();
      // Close window with no return value
      m_retVal = -2;
      return;
   }
}

//------------------------------------------------------------------------------

// Move camera
void ImageViewer::moveCursorUp(const int p_step, bool p_loop)
{
   // Previous image
   if (m_fitToScreen)
   {
   }
   // Scroll image
   m_camera.y += IMAGEVIEWER_SCROLL_SPEED;
   g_hasChanged = true;
}

void ImageViewer::moveCursorDown(const int p_step, bool p_loop)
{
   // Next image
   if (m_fitToScreen)
   {
   }
   // Scroll image
   m_camera.y -= IMAGEVIEWER_SCROLL_SPEED;
   g_hasChanged = true;
}

void ImageViewer::moveCursorLeft(const int p_step, bool p_loop)
{
   // Previous image
   if (m_fitToScreen)
   {
   }
   // Scroll image
   m_camera.x += IMAGEVIEWER_SCROLL_SPEED;
   g_hasChanged = true;
}

void ImageViewer::moveCursorRight(const int p_step, bool p_loop)
{
   // Next image
   if (m_fitToScreen)
   {
   }
   // Scroll image
   m_camera.x -= IMAGEVIEWER_SCROLL_SPEED;
   g_hasChanged = true;
}
