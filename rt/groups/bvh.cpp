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
    if (numPrimitives <= 0)
       return;
    node->bbox = BBox::empty();

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
    return root->bbox;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection result = Intersection::failure();

    // Does the ray intersect with the world?
    std::pair<float,float> dists = root->bbox.intersect(ray);
    float t1 = dists.first;
    float t2 = dists.second;
    if(t1 > t2){
        // nope
        return result;
    } 
    
    // create the stack with the root inside to begin
    std::vector<Node*> remainingNodes;
    remainingNodes.push_back(root);
    Node *currentNode;
    Intersection temp;

    while(!remainingNodes.empty()){
        // Intersec with last node from stack, delete it from stack
        currentNode = remainingNodes.back();
        remainingNodes.pop_back();
        // If current node does not have any childs, we intersec with its primitives
        if (currentNode->isLeaf){
            // std::cout << "->Leaf found" << std::endl;
            for(auto p : currentNode->primitives) {
                temp = p->intersect(ray, previousBestDistance);
                if (temp){
                    previousBestDistance = temp.distance;
                    result = temp;
                }
            }
        } else {
            //We intersec with its childs and add them to the stack if they succed

            // Intersec with left child
            dists = currentNode->leftChild->bbox.intersect(ray);
            t1 = dists.first;
            t2 = dists.second;
            if (t1 <= t2) {
                // std::cout << "-->leftChild added to stack" << std::endl;
                remainingNodes.push_back(currentNode->leftChild);
            }

            // Intersec with right child
            dists = currentNode->rightChild->bbox.intersect(ray);
            t1 = dists.first;
            t2 = dists.second;
            if (t1 <= t2) {
                // std::cout << "-->rightChild added to stack" << std::endl;
                remainingNodes.push_back(currentNode->rightChild);
            }
        }
    } 
    

    return result;
}

void BVH::add(Primitive* p) {
    primitives.push_back(p);
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