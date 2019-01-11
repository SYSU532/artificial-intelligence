"use strict";
//AStar algorithm
/// <reference path="./priority-queue.d.ts" />
function ArraySwapIndex(arr, indexA, indexB) {
    [arr[indexA], arr[indexB]] = [arr[indexB], arr[indexA]];
}
//Represent each node in the search graph, has reference to its parent
// and children node.
class node {
    constructor(state, currentBlank, parent) {
        this.parent = parent;
        this.state = state.slice();
        this.blankIndex = currentBlank;
        this.children = [];
        this.value = 0;
    }
    get identifier() {
        return this.state.toString();
    }
    get path() {
        let result = [];
        let curr = this;
        while (curr !== null) {
            result.unshift(curr);
            curr = curr.parent;
        }
        return result;
    }
    getChildren() {
        if (this.children.length !== 0) {
            return this.children;
        }
        if (this.blankIndex % 3 !== 2) {
            //Blank move right
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex + 1);
            this.children.push(new node(newState, this.blankIndex + 1, this));
        }
        if (this.blankIndex % 3 !== 0) {
            //Blank move left
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex - 1);
            this.children.push(new node(newState, this.blankIndex - 1, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 0) {
            //Blank move up
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex - 3);
            this.children.push(new node(newState, this.blankIndex - 3, this));
        }
        if (Math.floor(this.blankIndex / 3) !== 2) {
            //Blank move down
            let newState = this.state.slice();
            ArraySwapIndex(newState, this.blankIndex, this.blankIndex + 3);
            this.children.push(new node(newState, this.blankIndex + 3, this));
        }
        return this.children;
    }
}
//Abstract class
class searchMethod {
    constructor(initState, currentBlank) {
        this.openTable = new PriorityQueue({
            comparator: function (a, b) {
                return a.value - b.value;
            },
        });
        this.closedTable = {};
        this.currentNode = new node(initState, currentBlank, null);
        this.addNodeVal(this.currentNode)
        this.openTable.queue(this.currentNode);
        this.next();
        this.totalStep = 0;
        this.maxValue = this.currentNode.value;
    }
    next() {
        if (this.checkResult(this.currentNode.state)) {
            return [this.currentNode.state, this.currentNode.blankIndex];
        }
        this.totalStep++;
        if (this.openTable.length === 0) {
            alert("搜索失败");
            throw "Empty open table";
        }
        let newNode = this.openTable.peek();
        while ((newNode).identifier in this.closedTable) {
            this.openTable.dequeue();
            if (this.openTable.length === 0) {
                alert("搜索失败");
                throw "Empty open table";
            }
            newNode = this.openTable.peek();
        }
        this.openTable.dequeue();
        this.closedTable[newNode.identifier] = newNode;
        this.currentNode = newNode;
        if (this.currentNode.value > this.maxValue) {
            this.maxValue = this.currentNode.value;
        }
        let children = this.currentNode.getChildren();
        for (let child of children) {
            this.addNodeVal(child);
            if (child.value < 0) {
                continue;
            }
            if (child.value + 2 < this.currentNode.value) {
                alert("h(ni）<= 1+h(nj) Monotonicity violated!");
                throw "h(ni）<= 1+h(nj) Monotonicity violated!";
            }
            
            this.openTable.queue(child);
        }
        return [newNode.state, newNode.blankIndex];
    }
    getLowestNode() {
        return this.openTable.peek();
    }
    runAll() {
        while (true) {
            let [state, blank] = this.next();
            if (this.checkResult(state)) {
                break;
            }
        }
    }
    checkResult(state) {
        for (let i = 0; i < 9; i++) {
            if (state[i] !== i) {
                return false;
            }
        }
        if (this.currentNode.path.length < this.maxValue) {
            alert("f(n）<= f*(S0) violated!");
            console.log(this.maxValue);
        }
        return true;
    }
    get pathToCurrent() {
        return this.currentNode.path;
    }
    get steps() { return this.totalStep; }
}
class aStarH1 extends searchMethod {
    addNodeVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            //The cost from root to the current node, i.e g*(n)
            let currentCost = newNode.path.length;
            //The cost from current node to destination(h1*(n)) is estimated
            //by the distance of each misplaced number to its actual position.
            let estimatedMinCost = 0;
            for (let i = 0; i < newNode.state.length; i++) {
                if (i != newNode.blankIndex && newNode.state[i] !== i) {
                    estimatedMinCost++;
                }
            }
            newNode.value = currentCost + estimatedMinCost;
            
        } else {
            newNode.value = -1;
        }
    }
}
class aStarH2 extends searchMethod {
    addNodeVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            //The cost from root to the current node, i.e g*(n)
            let currentCost = newNode.path.length;
            //The cost from current node to destination(h1*(n)) is estimated
            //by the sum of the column and row differences in each misplaced position.
            let estimatedMinCost = 0;
            for (let i = 0; i < newNode.state.length; i++) {
                if (i == newNode.blankIndex) {
                    continue;
                }
                //Row differences
                estimatedMinCost += Math.abs(Math.floor(i / 3) - Math.floor(newNode.state[i] / 3));
                //Column differences
                estimatedMinCost += Math.abs(i % 3 - newNode.state[i] % 3);
            }
            newNode.value = currentCost + estimatedMinCost;
        } else {
            newNode.value = -1;
        }
    }
}
class bfs extends searchMethod {
    addNodeVal(newNode) {
        if (!(newNode.identifier in this.closedTable)) {
            if (newNode.parent) {
                newNode.value = newNode.parent.value + 1;
            } else {
                newNode.value = 0;
            }
        } else {
            newNode.value = -1;
        }
    }
}
