export interface VirtualFile {
  name: string;
  path: string;
  content: string;
  language: 'cpp' | 'hpp' | 'makefile' | 'cnf' | 'txt' | 'dat';
}

export interface ProjectConfig {
  elfName: string;
  videoMode: 'NTSC' | 'PAL';
  resolution: '640x448' | '512x448' | '640x512' | '320x240';
  aspectRatio: '4:3' | '16:9';
  audioFrequency: '44100' | '48000' | '22050';
  optimizationLevel: 'O0' | 'O1' | 'O2' | 'O3' | 'Os';
}

export interface ConsoleLog {
  id: string;
  type: 'info' | 'success' | 'warning' | 'error' | 'stdout' | 'iop';
  text: string;
  timestamp: string;
}

export interface PS2Stats {
  fps: number;
  drawCalls: number;
  vramAlloc: number; // in MB
  vramTotal: number; // 4MB
  ramAlloc: number;  // in MB
  ramTotal: number;  // 32MB
  iopAlloc: number;  // in MB
  iopTotal: number;  // 2MB
  activePads: number;
}
