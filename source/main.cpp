#include "../include/application.hpp"

int main() {
  Application app(Application::ApplicationMode::Sfml, "configs.txt");
  app.Run();
  return 0;
}