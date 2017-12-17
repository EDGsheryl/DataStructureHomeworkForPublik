
class Node {
    public Node fa;
    public Node lc;
    public Node rc;
    public int val;
}

class BinarySortTree {
    private Node root;

    BinarySortTree() {
        root = null;
    }

    public void insert(Node o, int q) {
        if (o == null) {
            o = new Node();
            o.val = q;
            return;
        }
        if (o.val > q) {
            if (o.lc == null) {
                o.lc = new Node();
                o.lc.fa = o;
                insert(o.lc, q);
            } else {
                insert(o.lc, q);
            }
        } else {
            if (o.rc == null) {
                o.rc = new Node();
                o.rc.fa = o;
                insert(o.rc, q);
            } else {
                insert(o.rc, q);
            }
        }
    }

    public void delete(Node o, int q) {
        if (o == null) {
            return;
        }
        if (o.val == q) {
            if (o.lc != null && o.rc == null) {
                o.val = o.lc.val;
                o.lc = o.lc.lc;
                o.rc = o.lc.rc;
                return;
            } else if (o.rc != null && o.lc == null) {
                o.val = o.rc.val;
                o.lc = o.rc.lc;
                o.rc = o.rc.rc;
                return;
            } else if (o.rc == null && o.lc == null) {
                if (o == root) {
                    root = null;
                    return;
                } else {
                    if (o.fa.lc == o) {
                        o.fa.lc = null;
                    } else {
                        o.fa.rc = null;
                    }
                }
            } else {
                Node now = o;
                now = now.lc;
                while (now.rc != null) now = now.rc;
                now.rc = o.rc;
                o.rc.fa = now;
                o.fa.lc = o.lc;
                o.lc.fa = o.fa;
            }
        }
        if (o.val > q) {
            delete(o.lc, q);
        } else {
            delete(o.rc, q);
        }
    }

    public void insert(int q) {
        insert(root, q);
    }

    public void delete(int q) {
        delete(root, q);
    }

    public void pre_order_traversal(Node o) {
        if (o == null) return;
        System.out.println(o.val);
        pre_order_traversal(o.lc);
        pre_order_traversal(o.rc);
    }

    public void in_order_traversal(Node o) {
        if (o == null) return;
        in_order_traversal(o.lc);
        System.out.println(o.val);
        in_order_traversal(o.rc);
    }

    public void post_order_traversal(Node o) {
        if (o == null) return;
        post_order_traversal(o.lc);
        post_order_traversal(o.rc);
        System.out.println(o.val);
    }

}

public class Main {
    public static void main(String[] args) {
        
    }
}
