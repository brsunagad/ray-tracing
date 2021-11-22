#include <rt/groups/bvh.h>

namespace rt {

BVH::BVH()
{
    /* TODO */
}

void BVH::rebuildIndex() {
    root->primitives = primitives;
    buildIndexStructure(root);
}

void BVH::buildIndexStructure(Node* node)
{
    int numPrimitives = node->primitives.size();
    //if (numPrimitives <= 0)
    //    return;

    for (int i = 0; i < numPrimitives; i++)
        node->extend(node->primitives[i]->getBounds());//extend bbox to include primitives

    if (numPrimitives < 3)//termination criteria
    {
        node->isLeaf = true;
        return;
    }
    else {
        node->isLeaf = false;
        node->leftChild = new Node();
        node->rightChild = new Node();

        int axisToSplit = findSplitAxis(node->bbox.diagonal());
        float splitLength = findSplitLength(axisToSplit, node->bbox);

        for (int i = 0; i < numPrimitives; i++) {
            float primitiveSplitLength = findSplitLength(axisToSplit, node->primitives[i]->getBounds());
            if (primitiveSplitLength <= splitLength) 
                node->leftChild->primitives.push_back(node->primitives[i]);
            else
                node->rightChild->primitives.push_back(node->primitives[i]);
        }

        if (node->leftChild->primitives.size() == 0)//to make sure child nodes have atleast one primitive
        {
            node->leftChild->primitives.push_back(node->rightChild->primitives[0]);
            node->rightChild->primitives.erase(node->rightChild->primitives.begin());
        }
        else if (node->rightChild->primitives.size() == 0)
        {
            node->rightChild->primitives.push_back(node->leftChild->primitives[0]);
            node->leftChild->primitives.erase(node->leftChild->primitives.begin());
        }
        buildIndexStructure(node->leftChild);
        buildIndexStructure(node->rightChild);
        return;
    }


}

float BVH::findSplitLength(int axis, BBox bbox) {
    if (axis == 0)
        return (bbox.min.x + bbox.max.x) / 2;
    else if (axis == 1)
        return (bbox.min.y + bbox.max.y) / 2;
    else 
        return (bbox.min.z + bbox.max.z) / 2;
}

int BVH::findSplitAxis(Vector vec) {
    if (vec.x > vec.y && vec.x > vec.z) return 0;
    else if (vec.y > vec.z) return 1;
    else return 2;
}

BBox BVH::getBounds() const {
    return this->root->bbox;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::add(Primitive* p) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

}