
declare interface block {
    moveFunc: () => void;
}

declare var pieces: block[];

declare var current_blank: number;

declare var startGame: () => void;

declare var printPicture: (seq: number[]) => void;


