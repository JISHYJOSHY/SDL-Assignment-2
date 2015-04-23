#include "BoundingBox.h"

BoundingBox::BoundingBox(void)
{
	radius = 0.217;
}

BoundingBox::~BoundingBox(void)
{
}

void BoundingBox::Create(std::vector<glm::vec3> verts)
{
	// here we go through all the vertices passed in to get the smallest and largest values (based on the verts)
	unsigned int numVerts = verts.size();
	for(int i = 0; i < numVerts; i++)
	{
		// first, we set the min and max to the first vert
		if(i > 0)
		{
			// we test the x axis, and edit the min or max
			if(verts[i].x < min.x)
				min.x = verts[i].x;
			else if(verts[i].x > max.x)
				max.x = verts[i].x;

			// we test the y axis, and edit the min or max
			if(verts[i].y < min.y)
				min.y = verts[i].y;
			else if(verts[i].y > max.y)
				max.y = verts[i].y;

			// we test the y axis, and edit the min or max
			if(verts[i].z < min.z)
				min.z = verts[i].z;
			else if(verts[i].z > max.z)
				max.z = verts[i].z;
		}
		else
			min = max = verts[i];
	}

	distance = CalculateDistance();
}

// Sphere contains Sphere
bool BoundingBox::SContainS(BoundingBox* box)
{
	float d = glm::distance(Center(), box->Center());

	return (d < getRadius() + box->getRadius());
}

// Sphere contains Cube
bool BoundingBox::SContainC(BoundingBox* box)
{
	// X aligned
	if(box->Center().x - box->Distance().x < Center().x + radius
	&& box->Center().x + box->Distance().x > Center().x - radius)
	{		
		// Y aligned
		if(box->Center().y - box->Distance().y < Center().y + radius
		&& box->Center().y + box->Distance().y > Center().y - radius)
		{	
			// Z aligned		
			if(box->Center().z - box->Distance().z < Center().z + radius
			&& box->Center().z + box->Distance().z > Center().z - radius)
			{
				return true;
			}
		}
	}
	return false;
}

// Cube contains Sphere
bool BoundingBox::CContainS(BoundingBox* box)
{
	// if X is aligned
	if(getMin().x < box->Center().x + box->getRadius()
	&& getMax().x > box->Center().x - box->getRadius())
	{
		// if Y is aligned
		if(getMin().y < box->Center().y + box->getRadius()
		&& getMax().y > box->Center().y - box->getRadius())
		{
			// if Z is aligned
			if(getMin().z < box->Center().z + box->getRadius()
			&& getMax().z > box->Center().z - box->getRadius())
			{
				return true;
			}			
		}		
	}
	return false;
}

// Cube contains Cube
bool BoundingBox::CContainC(BoundingBox* box)
{
	// X axis
	if(box->Center().x < Center().x + Distance().x
	&& box->Center().x > Center().x - Distance().x)
	{
		// Y axis
		if(box->Center().y < Center().y + Distance().y
		&& box->Center().y > Center().y - Distance().y)
		{
			// Y axis
			if(box->Center().z < Center().z + Distance().z
			&& box->Center().z > Center().z - Distance().z)
			{
				return true;
			}
		}
	}
	return false;
}

/// Return the center of the bounding box.
/// Using the max and min values, return the center.
glm::vec3 BoundingBox::Center()
{
	glm::vec3 distance = max - min;
	distance /= 2;

	return (max - distance);
}

/// Return the distance of the min and max values.
/// Using the max and min values, return the distance.
glm::vec3 BoundingBox::CalculateDistance()
{
	glm::vec3 d;
	d.x = glm::abs(min.x - max.x);
	d.y = glm::abs(min.y - max.y);
	d.z = glm::abs(min.z - max.z);

	return d;
}