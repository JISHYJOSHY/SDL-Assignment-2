#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_


#include <glm.hpp>
#include <vector>

class BoundingBox
{
public:
	BoundingBox(void);
	~BoundingBox(void);

	// Setup the bounding box
	void Create(std::vector<glm::vec3> verts);

	// Sphere contains Sphere
	bool SContainS(BoundingBox* box);
	// Sphere contains Cube
	bool SContainC(BoundingBox* box);
	// Cube contains Sphere
	bool CContainS(BoundingBox* box);
	// Cube contains Cube
	bool CContainC(BoundingBox* box);

	/// Return the center
	glm::vec3 Center();

	/// Return the distance
	inline glm::vec3 Distance() { return distance; };

	inline float getRadius() { return radius; };
	inline glm::vec3 getDistance() { return distance; };

	inline glm::vec3 getMin() { return min; };
	inline glm::vec3 getMax() { return max; };

private:
	glm::vec3 min, max;
	
	// Set the distance between the individual points, not the vec3
	glm::vec3 CalculateDistance();
	glm::vec3 distance;
	
	float radius;
};

#endif