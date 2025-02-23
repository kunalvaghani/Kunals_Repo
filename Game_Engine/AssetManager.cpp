#include "AssetManager.h"

AssetManager::AssetManager(): isCreated(false) {
	//meshes
	AddComponent<MeshComponent>("SM_Plane", nullptr, "meshes/Plane.obj");
	AddComponent<MeshComponent>("SM_CheckerPiece", nullptr, "meshes/CheckerPiece.obj");
	AddComponent<MeshComponent>("SM_Sphere", nullptr, "meshes/Sphere.obj");
	//shaders
	AddComponent<ShaderComponent>("S_Texture", nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");

	//materials
	AddComponent<MaterialComponent>("M_CheckerBoard", nullptr, "textures/8x8_checkered_board.png");
	AddComponent<MaterialComponent>("M_WhiteChecker", nullptr, "textures/whiteCheckerPiece.png");
	AddComponent<MaterialComponent>("M_RedChecker", nullptr, "textures/redCheckerPiece.png");

	ListAllComponents();
	OnCreate();
}

AssetManager::~AssetManager() {
	RemoveAllComponents();
}

bool AssetManager::OnCreate() {
	if (isCreated) return isCreated;
	for (std::pair<const char*, Ref<Component>> c : componentCatalog) {
		if (!c.second->OnCreate()) {
			isCreated = false;
		}
	}
	return isCreated;
}

void AssetManager::RemoveAllComponents() {
	componentCatalog.clear();
}

void AssetManager::ListAllComponents() const {
	std::cout <<"\n"<< typeid(*this).name() << " contain the following components:\n";
	for (auto c : componentCatalog) {
		std::cout <<"\t" << c.first << ": " << typeid(*(c.second.get())).name() << "\n";
	}
	std::cout << "\n";
}
