#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <rt/primitive.h>
namespace rt {

class  Node
{
public:
    Node() {}
    ~Node() {}
    BBox bbox = BBox::empty();
    bool isLeaf;
    Node* leftChild;
    Node* rightChild;

    void extend(const BBox& newBox) {
        bbox.extend(newBox);
    }

    typedef std::vector<Primitive*> Primitives;
    Primitives primitives;

};

class BVH : public Group {
private:
    Node* root = new Node();
    int count;
public:
    BVH();
    ~BVH();
    void deleteTree(Node* node);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void rebuildIndex();
    void buildIndexStructure(Node* root);
    float findMidPoint(int axis, BBox bbox);
    int findSplitAxis(Vector vec);
    float getCoordOnAxis(int axis, Point point);
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);

    // Do not use this structure as your node layout:
    // It is inefficient and has a large memory footprint.
    struct SerializedNode {
        bool isLeaf;
        BBox bbox;

        // For leaves only
        std::vector<Primitive*> primitives;

        // For internal nodes only
        size_t leftChildId;
        size_t rightChildId;
    };

    // Implement this function if you want to take part in the BVH speed competition
    struct Output {
        virtual void setNodeCount(size_t nodeCount) = 0;
        virtual void setRootId(size_t rootId) = 0;
        virtual void writeNode(size_t nodeId, const SerializedNode& node) = 0;
    };
    void serialize(Output& output);

    // Implementing this is optional and not needed for the BVH speed competition,
    // but it will allow you to run the benchmark utility and test your BVH exporter.
    struct Input {
        virtual size_t getNodeCount() = 0;
        virtual size_t getRootId() = 0;
        virtual const SerializedNode& readNode(size_t nodeId) = 0;
    };
    void deserialize(Input& input);
};

}

#endif