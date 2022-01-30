#define SAH
#include <rt/groups/bvh.h>

namespace rt {

BVH::BVH()
{
    /* TODO */
   
}

BVH::~BVH()
{
    //std::cout << "\nDeleting BVH tree..." << std::endl;
    //deleteTree(root);
    //std::cout << "Deleted BVH tree successfully"<<std::endl;
}

void BVH::deleteTree(Node* node)
{
    if (node == NULL) return;

    /* first delete both subtrees */
    if (node->isLeaf == false) {
        if (node->leftChild != NULL)
            deleteTree(node->leftChild);
        if (node->rightChild != NULL)
            deleteTree(node->rightChild);
    }
    /* then delete the node */
   
    delete node;
}

void BVH::rebuildIndex() {
    root->primitives = primitives;
   // primitives.clear();
   std::cout << "\nBuilding BVH tree..." << std::endl;

    buildIndexStructure(root);

    std::cout << "Builded BVH tree successfully" << std::endl;
}

void BVH::buildIndexStructure(Node* node)
{
    int numPrimitives = node->primitives.size();
    if (numPrimitives <= 0)
       return;

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
        float splitPoint = findMidPoint(axisToSplit, node->bbox);

#ifdef SAH //SAH
        {
        int numbins = 40;
        
        float totalCost=0, lcCost=0, rcCost=0, bestCost = FLT_MAX;
        for (int j = 1; j < numbins; j++) {
            /*Node* tempLChild = new Node();
            Node* tempRChild = new Node();*/
            float splitLen = getCoordOnAxis(axisToSplit,node->bbox.min) + j * (getCoordOnAxis(axisToSplit, node->bbox.max)- getCoordOnAxis(axisToSplit, node->bbox.min))/numbins;
            int countL = 0, countR = 0;
            BBox areaL = BBox::empty(), areaR = BBox::empty();
            for (int i = 0; i < numPrimitives; i++) {

                float primitiveSplitMidPoint = findMidPoint(axisToSplit, node->primitives[i]->getBounds());

                if (primitiveSplitMidPoint <= splitLen) {
                    //tempLChild->primitives.push_back(node->primitives[i]);
                    //tempLChild->extend(node->primitives[i]->getBounds());
                    countL++;
                    areaL.extend(node->primitives[i]->getBounds());

                }
                else {
                    //tempRChild->primitives.push_back(node->primitives[i]);
                    //tempRChild->extend(node->primitives[i]->getBounds());
                    countR++;
                    areaR.extend(node->primitives[i]->getBounds());
                }
            }
            /*if(tempLChild->primitives.size() != 0)
                lcCost = tempLChild->primitives.size() * tempLChild->bbox.area()/node->bbox.area() ;
            if (tempRChild->primitives.size() != 0)
                rcCost = tempRChild->primitives.size() * tempRChild->bbox.area() / node->bbox.area();*/
            if (countL > 0)
                lcCost = countL * areaL.area() / node->bbox.area();
            if (countR > 0)
                rcCost = countR * areaR.area() / node->bbox.area();
            totalCost = lcCost + rcCost;
            if (totalCost <= bestCost) {
                bestCost = totalCost;
                splitPoint = splitLen;
            }

        }
    }
#endif  // end SAH 
        //Time taken to render a3-2.png: 3086.39ms without SAH
        //Time taken to render a3-2.png: 3059.73ms with SAH

        for (int i = 0; i < numPrimitives; i++) {
            float primitiveSplitMidPoint = findMidPoint(axisToSplit, node->primitives[i]->getBounds());
            if (primitiveSplitMidPoint <= splitPoint)
                node->leftChild->primitives.push_back(node->primitives[i]);
            else
                node->rightChild->primitives.push_back(node->primitives[i]);
        }

        node->primitives.clear();//clear parents primitives as only leaf nodes store primitives
        assert(node->primitives.size()==0);
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
void BVH::setenv(Primitive* p) {
    useEnv = true;
    envMap = p;
}


float BVH::findMidPoint(int axis, BBox bbox) {
    if (axis == 0)
        return (bbox.min.x + bbox.max.x) / 2;
    else if (axis == 1)
        return (bbox.min.y + bbox.max.y) / 2;
    else 
        return (bbox.min.z + bbox.max.z) / 2;
}

float BVH::getCoordOnAxis(int axis, Point point) {
    if (axis == 0)
        return point.x;
    else if (axis == 1)
        return point.y;
    else
        return point.z;
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
    if (useEnv && !result) {
        result = envMap->intersect(ray, previousBestDistance);
    }

    return result;
}

void BVH::add(Primitive* p) {
    primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    for (auto p : primitives) 
        p->setMaterial(m);
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