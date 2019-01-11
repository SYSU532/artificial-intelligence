declare type Comparator<T> = (a: T, b: T) => number;
declare interface Options<T> {
    comparator: Comparator<T>;
    initialValues?: T[];
    strategy?: any;
}
declare interface QueueStrategy<T> {
    queue(value: T): void;
    dequeue(): T;
    peek(): T;
    clear(): void;
}
declare class PriorityQueue<T> {
    private _length;
    readonly length: number;
    private strategy;
    constructor(options: Options<T>);
    queue(value: T): void;
    dequeue(): T;
    peek(): T;
    clear(): void;
}
