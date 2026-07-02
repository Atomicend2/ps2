import React, { useState, useEffect, useRef } from 'react';
import { Cpu, Terminal, Play, RotateCcw, AlertTriangle, Layers, Gamepad, Tv, Activity, Sparkles, Skull, ShieldAlert } from 'lucide-react';
import { ConsoleLog, PS2Stats, ProjectConfig } from '../types';

interface SimulatorProps {
  config: ProjectConfig;
  onCompilationStart: () => void;
}

const GAME_CHAPTERS = [
  {
    chapterId: 0,
    title: "Chapter 1: The Holy War of Elyndra (Act I)",
    region: "Holy Plains of Valerius",
    architecture: "Gothic Cathedral Architecture",
    sin: "PRIDE (Tyr - Sacrifice)",
    vowType: "Vow of Protection",
    speaker: "Valerius High Priest",
    line: "Xyven, do you swear to protect the Cathedral and sacrifice your blood to the divine engine?",
    choiceA: "Yes, on my honor.",
    choiceB: "Is our family's honor merely a cage?",
    successLog: "[NARRATIVE] Xyven binds his life to the altar. Vow strength increased.",
    zones: ["Plains Sanctuary Gates (0x01)", "Cathedral Courtyard (0x02)", "High Choir Altar (0x03)"],
    scriptFile: "scripts/chapter_1.txt"
  },
  {
    chapterId: 1,
    title: "Chapter 2: Chains of Military Rank (Act II)",
    region: "Grand Iron Fortress",
    architecture: "Brutalist Heavy Stone Fortifications",
    sin: "WRATH (Morvain - Conquest)",
    vowType: "Vow of Strength",
    speaker: "General Vance",
    line: "Obey. Order your squad to hold the line at all costs. Feed them to the wolves for victory!",
    choiceA: "I will shield them with my own body!",
    choiceB: "Tactical retreat is wiser.",
    successLog: "[NARRATIVE] Xyven takes the front lines. The squad survives, but the burden grows.",
    zones: ["Outpost Barricades (0x01)", "Fortress Armory Vaults (0x02)", "Command War Chamber (0x03)"],
    scriptFile: "scripts/chapter_2.txt"
  },
  {
    chapterId: 2,
    title: "Chapter 3: The Dark Origins of the Vows (Act III)",
    region: "The Glimmering Abyss",
    architecture: "Sunken Crystalline Monoliths",
    sin: "GREED (Kaelor - Blind Obedience)",
    vowType: "Vow of Faith",
    speaker: "Ancient Echo",
    line: "The vows are a fracture of your own soul. Do you accept the scar for ultimate power?",
    choiceA: "I accept the scar to save my brother.",
    choiceB: "Is there no other way?",
    successLog: "[NARRATIVE] A dark fracture splits Xyven's soul. Weapon damage surges.",
    zones: ["Crystalline Descent (0x01)", "Deep Sunken Monoliths (0x02)", "Shattered Abyss Temple (0x03)"],
    scriptFile: "scripts/chapter_3.txt"
  },
  {
    chapterId: 3,
    title: "Chapter 4: Whispering Experimentation of Seris (Act IV)",
    region: "Whispering Woods of Seris",
    architecture: "Bio-Organic Sylvan Laboratories",
    sin: "LUST (Seris - Human Experimentation)",
    vowType: "Vow of Mercy",
    speaker: "Inquisitor Malakor",
    line: "We slice open these heretics to extract the pure vows. This is holy medicine, Xyven!",
    choiceA: "Stop this horror!",
    choiceB: "Are we any different from the monsters?",
    successLog: "[NARRATIVE] Xyven lashing out. The lab is shattered, but the poison lingers.",
    zones: ["Sylvan Wood Boundaries (0x01)", "Healing Bio-Laboratories (0x02)", "Extract Incubation Vats (0x03)"],
    scriptFile: "scripts/chapter_4.txt"
  },
  {
    chapterId: 4,
    title: "Chapter 5: Prismatic Spires of Manipulation (Act V)",
    region: "The Glass Spires of Lys",
    architecture: "Prismatic Floating Mirror Spires",
    sin: "COVETOUS (Lys - Manipulation)",
    vowType: "Vow of Wisdom",
    speaker: "Lady Lys",
    line: "Your brother is molded into a sacrificial lamb. Will you save him or the kingdom?",
    choiceA: "I will burn this entire kingdom!",
    choiceB: "I will find another way, even if it breaks us.",
    successLog: "[NARRATIVE] SIF registers overridden. Aevior's sacrifice is bound into the glass scepter.",
    zones: ["Prismatic Mirror Bridge (0x01)", "Prismatic Wisdom Spires (0x02)", "Throne of Reflection (0x03)"],
    scriptFile: "scripts/chapter_5.txt"
  },
  {
    chapterId: 5,
    title: "Chapter 6: The Betrayal at Broken Spires (Act VI)",
    region: "The Broken Spires of Ardent",
    architecture: "Fractured Floating Shards",
    sin: "ENVY (Ardent - Despair)",
    vowType: "Vow of Hope",
    speaker: "Aevior (Brother)",
    line: "Xyven, stop! I must complete the ritual. Why don't you trust me?!",
    choiceA: "Because they are using you!",
    choiceB: "If you choose them, we clash!",
    successLog: "[NARRATIVE] The sky bleeds. The sacred war collapses into tragedy.",
    zones: ["Ardent Floating Ravine (0x01)", "Broken Spires Crossing (0x02)", "Altar of Clashing Fates (0x03)"],
    scriptFile: "scripts/chapter_6.txt"
  },
  {
    chapterId: 6,
    title: "Chapter 7: The Swamps of Lys (Act VII)",
    region: "Misty Marsh Shore",
    architecture: "Submerged Limestone Steps and Dark Waterways",
    sin: "GLUTTONY (Lys - Submersion)",
    vowType: "Vow of Purity",
    speaker: "Swamp Hermit",
    line: "The water of the baptistry turns to pitch, Xyven. Do you submerge your sword in the black water to wash the scars?",
    choiceA: "I will cleanse the blade, whatever the cost.",
    choiceB: "No, this water is tainted with heretic souls.",
    successLog: "[NARRATIVE] Xyven purges his sword, but the toxic sludge clings to his armor.",
    zones: ["Misty Marsh Shore (0x01)", "Moss Tree Bridge (0x02)", "Sunken Baptistry Arena (0x03)"],
    scriptFile: "scripts/chapter_7.txt"
  },
  {
    chapterId: 7,
    title: "Chapter 8: The Foundries of Ardent (Act VIII)",
    region: "Smelting Core Cathedral",
    architecture: "Heavy Industrial Mechanical Conveyors",
    sin: "SLOTH (Ardent - Mechanization)",
    vowType: "Vow of Industry",
    speaker: "Grand Marshal Vane",
    line: "The foundries work day and night to forge the vessel, Xyven. Yield and accept your place in the gear!",
    choiceA: "I will shatter the gears!",
    choiceB: "Your machine is a tomb.",
    successLog: "[NARRATIVE] The foundries explode, molten gold leaking onto basalt rock.",
    zones: ["Assembly Belts (0x01)", "Piston Hazards (0x02)", "Smelting Core (0x03)"],
    scriptFile: "scripts/chapter_8.txt"
  },
  {
    chapterId: 8,
    title: "Chapter 9: The Seventh Vow Climax (Act IX)",
    region: "The Infinite Mirror Plane",
    architecture: "Shattered Mirror-Floor Void",
    sin: "SLOTH / THE CYCLE (Valen - Control)",
    vowType: "The Seventh Vow",
    speaker: "The Oath-Binder God",
    line: "You stand before the foundational core of Elyndra. Submit to the loop, or shatter the Seventh Vow and plunge the world into darkness!",
    choiceA: "Shatter the Seventh Vow! (Canon)",
    choiceB: "Submit to the Loop and restart the cycle.",
    successLog: "",
    zones: ["Infinite Mirror (0x01)", "True Altar (0x02)", "The Core Reset Vector (0x03)"],
    scriptFile: "scripts/chapter_9.txt"
  }
];

export const Simulator: React.FC<SimulatorProps> = ({ config }) => {
  const [activeTab, setActiveTab] = useState<'screen' | 'compiler' | 'ee' | 'iop' | 'vram' | 'dvd'>('compiler');
  const [isCompiling, setIsCompiling] = useState(false);
  const [isRunning, setIsRunning] = useState(false);
  const [compilerProgress, setCompilerProgress] = useState(0);
  
  // Interactive Gameplay & Zone/Script-Streaming State
  const [currentChapterIdx, setCurrentChapterIdx] = useState<number>(0);
  const [activeZoneIdx, setActiveZoneIdx] = useState<number>(0);
  const [isZoneLoading, setIsZoneLoading] = useState<boolean>(false);
  const [zoneLoadingProgress, setZoneLoadingProgress] = useState<number>(0);
  const [dvdReadSpeed, setDvdReadSpeed] = useState<string>('4x CAV');
  const [activeDvdSector, setActiveDvdSector] = useState<number>(14520);

  const [dialogueActive, setDialogueActive] = useState<boolean>(true);
  const [selectedChoice, setSelectedChoice] = useState<number | null>(null);
  const [vowStrength, setVowStrength] = useState<number>(10);
  const [burdenScars, setBurdenScars] = useState<number>(0);
  const [maxHealthMod, setMaxHealthMod] = useState<number>(100);
  const [isGlitching, setIsGlitching] = useState<boolean>(false);
  const [glitchMessage, setGlitchMessage] = useState<string>('');
  const [cameraYaw, setCameraYaw] = useState<number>(0);
  const [isEpilogue, setIsEpilogue] = useState<boolean>(false);
  const [typedLine, setTypedLine] = useState('');

  // DualShock 2 Rumble & Physical Feedback Simulator State
  const [isRumbling, setIsRumbling] = useState<boolean>(false);
  const [rumbleLeftMotor, setRumbleLeftMotor] = useState<number>(0); // Large weights (low freq)
  const [rumbleRightMotor, setRumbleRightMotor] = useState<number>(0); // Small weights (high freq)
  const [rumbleStutterMsg, setRumbleStutterMsg] = useState<string>('');
  const [isScreenShaking, setIsScreenShaking] = useState<boolean>(false);

  const [stats, setStats] = useState<PS2Stats>({
    fps: 0,
    drawCalls: 0,
    vramAlloc: 0,
    vramTotal: 4.0,
    ramAlloc: 0,
    ramTotal: 32.0,
    iopAlloc: 0,
    iopTotal: 2.0,
    activePads: 0,
  });

  const eeLogsEndRef = useRef<HTMLDivElement>(null);
  const iopLogsEndRef = useRef<HTMLDivElement>(null);
  const compilerLogsEndRef = useRef<HTMLDivElement>(null);
  const canvasRef = useRef<HTMLCanvasElement | null>(null);

  const [eeLogs, setEeLogs] = useState<ConsoleLog[]>([]);
  const [iopLogs, setIopLogs] = useState<ConsoleLog[]>([]);
  const [compilerLogs, setCompilerLogs] = useState<ConsoleLog[]>([]);

  // Append a log helper
  const addLog = (
    type: ConsoleLog['type'],
    text: string,
    target: 'ee' | 'iop' | 'compiler'
  ) => {
    const timestamp = new Date().toLocaleTimeString();
    const newLog: ConsoleLog = {
      id: Math.random().toString(),
      type,
      text,
      timestamp,
    };
    if (target === 'ee') setEeLogs(prev => [...prev, newLog]);
    if (target === 'iop') setIopLogs(prev => [...prev, newLog]);
    if (target === 'compiler') setCompilerLogs(prev => [...prev, newLog]);
  };

  // Auto-scroll logs
  useEffect(() => {
    if (activeTab === 'ee') eeLogsEndRef.current?.scrollIntoView({ behavior: 'smooth' });
    if (activeTab === 'iop') iopLogsEndRef.current?.scrollIntoView({ behavior: 'smooth' });
    if (activeTab === 'compiler') compilerLogsEndRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [eeLogs, iopLogs, compilerLogs, activeTab]);

  // Initial setup logs
  useEffect(() => {
    addLog('info', '=======================================================', 'compiler');
    addLog('info', '  mips64r5900el-ps2-elf-g++ toolchain ready', 'compiler');
    addLog('info', '  Tyra open-source engine headers loaded successfully', 'compiler');
    addLog('info', '  Click "Compile & Boot Game" to build SEVENTH_VOW.ELF', 'compiler');
    addLog('info', '=======================================================', 'compiler');

    addLog('info', '[BIOS] System initialized. IOP hardware bridges online.', 'ee');
    addLog('info', '[BIOS] Loading kernel boot modules...', 'ee');
    addLog('warning', '[BIOS] No valid disc inserted or BOOT2 target specified.', 'ee');

    addLog('iop', 'iop_sound_core: Driver audsrv v1.2 loaded into IOP RAM.', 'iop');
    addLog('iop', 'iop_sif: Registering SIF core interface channels...', 'iop');
    addLog('iop', 'iop_pad: PAD dualshock registers listening on Port 1, Port 2.', 'iop');
  }, []);

  // Typewriter Subtitles effect
  useEffect(() => {
    if (!isRunning || isEpilogue) return;
    let active = true;
    let i = 0;
    setTypedLine('');
    const lineText = GAME_CHAPTERS[currentChapterIdx]?.line || '';
    if (!lineText) return;
    const interval = setInterval(() => {
      if (!active) return;
      setTypedLine(prev => prev + lineText.charAt(i));
      i++;
      if (i >= lineText.length) {
        clearInterval(interval);
      }
    }, 15);
    return () => {
      active = false;
      clearInterval(interval);
    };
  }, [currentChapterIdx, isRunning, isEpilogue]);

  // Frame tick simulation when game is running
  useEffect(() => {
    if (!isRunning) {
      setStats({
        fps: 0,
        drawCalls: 0,
        vramAlloc: 0,
        vramTotal: 4.0,
        ramAlloc: 0,
        ramTotal: 32.0,
        iopAlloc: 0,
        iopTotal: 2.0,
        activePads: 0,
      });
      return;
    }

    let frameCount = 0;
    const maxFps = config.videoMode === 'NTSC' ? 60 : 50;

    const interval = setInterval(() => {
      frameCount++;
      const currentFps = Math.floor(maxFps - Math.random() * 1.5);
      const randDrawCalls = Math.floor(210 + Math.random() * 35);
      const randVram = Number((1.24 + Math.sin(frameCount * 0.05) * 0.08).toFixed(2));
      const randRam = Number((12.4 + Math.sin(frameCount * 0.01) * 0.2).toFixed(1));
      const randIop = Number((0.68 + Math.sin(frameCount * 0.02) * 0.03).toFixed(2));

      setStats({
        fps: currentFps,
        drawCalls: randDrawCalls,
        vramAlloc: randVram,
        vramTotal: 4.0,
        ramAlloc: randRam,
        ramTotal: 32.0,
        iopAlloc: randIop,
        iopTotal: 2.0,
        activePads: 1,
      });

      // Periodically output standard EE engine logs
      if (frameCount % 60 === 0) {
        const activeRegionName = GAME_CHAPTERS[currentChapterIdx]?.region || "None";
        addLog('stdout', `[EE] GS Render: Region='${activeRegionName}' | FPS: ${currentFps} | Draw Calls: ${randDrawCalls}`, 'ee');
      }
      if (frameCount % 120 === 0 && !isEpilogue) {
        addLog('stdout', `[EE] Camera updated. Target Orbit Pitch: 0.50 | Yaw: ${cameraYaw.toFixed(2)}`, 'ee');
      }
      if (frameCount % 200 === 0) {
        addLog('iop', '[IOP] Audio: ADPCM Voice stream OK. Playing Chapter background wav stream.', 'iop');
      }
    }, 1000 / maxFps);

    return () => clearInterval(interval);
  }, [isRunning, config.videoMode, currentChapterIdx, cameraYaw, isEpilogue]);

  // Real-time canvas 3D projection rendering
  useEffect(() => {
    if (activeTab !== 'screen' || !isRunning || isEpilogue) return;
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    let animId: number;
    let angle = 0;

    const render = () => {
      angle += 0.015;
      const width = canvas.width;
      const height = canvas.height;
      ctx.clearRect(0, 0, width, height);

      ctx.save();

      // Physical screen shaking translation based on burdenScars
      if (isScreenShaking) {
        const shakeIntensity = 3.5 + burdenScars * 1.5;
        const dx = (Math.random() - 0.5) * shakeIntensity;
        const dy = (Math.random() - 0.5) * shakeIntensity;
        ctx.translate(dx, dy);
      }

      // Curved radial overlay backround
      const grad = ctx.createRadialGradient(width / 2, height / 2, 10, width / 2, height / 2, width);
      grad.addColorStop(0, '#0d1117');
      grad.addColorStop(1, '#05070a');
      ctx.fillStyle = grad;
      ctx.fillRect(0, 0, width, height);

      // CRT Scanline patterns
      ctx.strokeStyle = 'rgba(255, 255, 255, 0.035)';
      ctx.lineWidth = 1;
      for (let y = 0; y < height; y += 4) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(width, y);
        ctx.stroke();
      }

      // Color scheme for current chapter context
      let color = '#3b82f6'; // Default Blue
      if (currentChapterIdx === 0) color = '#f59e0b'; // Amber - Pride
      if (currentChapterIdx === 1) color = '#ef4444'; // Red - Wrath
      if (currentChapterIdx === 2) color = '#06b6d4'; // Cyan - Greed
      if (currentChapterIdx === 3) color = '#10b981'; // Green - Lust
      if (currentChapterIdx === 4) color = '#a855f7'; // Purple - Covetousness
      if (currentChapterIdx === 5) color = '#f43f5e'; // Rose - Envy
      if (currentChapterIdx === 6) color = '#14b8a6'; // Teal - Gluttony (Lys Swamp)
      if (currentChapterIdx === 7) color = '#f97316'; // Orange - Sloth (Foundry)
      if (currentChapterIdx === 8) color = '#e11d48'; // Crimson - Climax (The Final Seventh Vow)

      if (isGlitching) {
        color = Math.random() > 0.35 ? '#dc2626' : '#1e1e1e';
      }

      ctx.strokeStyle = color;
      ctx.lineWidth = 1;

      // Project parameters
      const centerY = height / 2 - 10;
      const centerX = width / 2;
      const pitch = 0.55 + Math.sin(angle * 0.4) * 0.15;
      const yaw = angle + cameraYaw;

      const project = (x: number, y: number, z: number) => {
        let x1 = x * Math.cos(yaw) - z * Math.sin(yaw);
        let z1 = x * Math.sin(yaw) + z * Math.cos(yaw);
        let y1 = y * Math.cos(pitch) - z1 * Math.sin(pitch);
        let z2 = y * Math.sin(pitch) + z1 * Math.cos(pitch);

        const distance = 200;
        const scale = distance / (distance + z2);
        return {
          x: centerX + x1 * scale * 1.5,
          y: centerY + y1 * scale * 1.5
        };
      };

      // Draw perspective wireframe grid
      ctx.strokeStyle = color + '1a';
      for (let i = -5; i <= 5; i++) {
        ctx.beginPath();
        let p1 = project(i * 30, 45, -150);
        let p2 = project(i * 30, 45, 150);
        ctx.moveTo(p1.x, p1.y);
        ctx.lineTo(p2.x, p2.y);
        ctx.stroke();

        ctx.beginPath();
        let p3 = project(-150, 45, i * 30);
        let p4 = project(150, 45, i * 30);
        ctx.moveTo(p3.x, p3.y);
        ctx.lineTo(p4.x, p4.y);
        ctx.stroke();
      }

      // Draw central rotating 3D crystal sword
      ctx.strokeStyle = color;
      ctx.shadowColor = color;
      ctx.shadowBlur = 8;
      ctx.lineWidth = 1.2;

      const top = project(0, -55, 0);
      const bottom = project(0, 35, 0);
      const left = project(-18, 0, -18);
      const right = project(18, 0, -18);
      const front = project(0, 0, 18);
      const back = project(0, 0, -36);

      const drawLine = (pA: any, pB: any) => {
        ctx.beginPath();
        ctx.moveTo(pA.x, pA.y);
        ctx.lineTo(pB.x, pB.y);
        ctx.stroke();
      };

      drawLine(top, left);
      drawLine(top, right);
      drawLine(top, front);
      drawLine(top, back);
      drawLine(bottom, left);
      drawLine(bottom, right);
      drawLine(bottom, front);
      drawLine(bottom, back);
      drawLine(left, front);
      drawLine(front, right);
      drawLine(right, back);
      drawLine(back, left);

      ctx.shadowBlur = 0; // reset shadow

      // DualShock rumble impact neon slashes (SMT style)
      if (isRumbling) {
        ctx.strokeStyle = '#ff3300';
        ctx.lineWidth = 3;
        ctx.shadowColor = '#ff3300';
        ctx.shadowBlur = 12;
        
        ctx.beginPath();
        ctx.moveTo(width * 0.05, height * 0.15 + Math.random() * 50);
        ctx.lineTo(width * 0.95, height * 0.85 - Math.random() * 50);
        ctx.stroke();
        
        ctx.strokeStyle = '#00ffff';
        ctx.lineWidth = 1.5;
        ctx.beginPath();
        ctx.moveTo(width * 0.9, height * 0.1 + Math.random() * 50);
        ctx.lineTo(width * 0.1, height * 0.9 - Math.random() * 50);
        ctx.stroke();
        ctx.shadowBlur = 0;
      }

      // Dynamic warning overlays during choice overrides
      if (isGlitching) {
        ctx.fillStyle = 'rgba(239, 68, 68, 0.12)';
        ctx.fillRect(0, 0, width, height);

        ctx.fillStyle = '#ef4444';
        for (let idx = 0; idx < 6; idx++) {
          ctx.fillRect(
            Math.random() * width,
            Math.random() * height,
            Math.random() * 60 + 20,
            Math.random() * 8 + 2
          );
        }
      }

      ctx.restore();

      animId = requestAnimationFrame(render);
    };

    render();
    return () => cancelAnimationFrame(animId);
  }, [activeTab, isRunning, currentChapterIdx, cameraYaw, isGlitching, isEpilogue, isScreenShaking, isRumbling, burdenScars]);

  const handleCompileAndBoot = () => {
    if (isCompiling || isRunning) return;
    setIsCompiling(true);
    setActiveTab('compiler');
    setCompilerProgress(0);
    setCompilerLogs([]);

    const steps = [
      { text: 'mips64r5900el-ps2-elf-g++ -D_EE -O3 -fno-exceptions -fno-rtti -Wall -Iinclude -Isrc -c src/main.cpp -o obj/main.o', delay: 250 },
      { text: 'Compiling src/main.cpp...', delay: 50 },
      { text: 'mips64r5900el-ps2-elf-g++ -D_EE -O3 -fno-exceptions -fno-rtti -Wall -Iinclude -Isrc -c src/game.cpp -o obj/game.o', delay: 300 },
      { text: 'Compiling src/game.cpp...', delay: 50 },
      { text: 'mips64r5900el-ps2-elf-g++ -D_EE -O3 -fno-exceptions -fno-rtti -Wall -Iinclude -Isrc -c src/vow_system.cpp -o obj/vow_system.o', delay: 150 },
      { text: 'Compiling src/vow_system.cpp...', delay: 50 },
      { text: 'mips64r5900el-ps2-elf-g++ -D_EE -O3 -fno-exceptions -fno-rtti -Wall -Iinclude -Isrc -c src/chapter_manager.cpp -o obj/chapter_manager.o', delay: 200 },
      { text: 'Compiling src/chapter_manager.cpp...', delay: 50 },
      { text: 'mips64r5900el-ps2-elf-g++ -D_EE -O3 -fno-exceptions -fno-rtti -Wall -Iinclude -Isrc -c src/dialogue_engine.cpp -o obj/dialogue_engine.o', delay: 180 },
      { text: 'Compiling src/dialogue_engine.cpp...', delay: 50 },
      { text: `Linking object files: ${config.elfName}`, delay: 200 },
      { text: `mips64r5900el-ps2-elf-g++ -T${config.videoMode === 'NTSC' ? 'linkfile_ntsc' : 'linkfile_pal'} -Llib -o ${config.elfName} obj/main.o obj/game.o obj/vow_system.o obj/chapter_manager.o obj/dialogue_engine.o -ltyra -lpadx -laudsrv -lpng -lz -lm`, delay: 300 },
      { text: 'Stripping debug symbols to compress footprint...', delay: 100 },
      { text: `mips64r5900el-ps2-elf-strip --strip-all ${config.elfName}`, delay: 100 },
      { text: '=======================================================', delay: 50 },
      { text: `  Build Successful: ${config.elfName} (${config.videoMode} mode)`, delay: 50 },
      { text: '  Ready to load via cdrom0:\\\\ device mapping', delay: 50 },
      { text: '=======================================================', delay: 50 },
    ];

    let currentStepIdx = 0;
    
    const executeStep = () => {
      if (currentStepIdx >= steps.length) {
        setIsCompiling(false);
        setIsRunning(true);
        bootPS2();
        return;
      }

      const step = steps[currentStepIdx];
      const isSuccessMsg = step.text.includes('Successful') || step.text.includes('Linking') || step.text.includes('Compiling');
      addLog(isSuccessMsg ? 'success' : 'info', step.text, 'compiler');
      
      setCompilerProgress(Math.floor(((currentStepIdx + 1) / steps.length) * 100));
      currentStepIdx++;
      setTimeout(executeStep, step.delay);
    };

    executeStep();
  };

  const bootPS2 = () => {
    setActiveTab('screen'); // Automatically open screen to play the game!
    setEeLogs([]);
    setIopLogs([]);
    
    // Reset state
    setCurrentChapterIdx(0);
    setActiveZoneIdx(0);
    setDialogueActive(true);
    setSelectedChoice(null);
    setVowStrength(10);
    setBurdenScars(0);
    setMaxHealthMod(100);
    setIsGlitching(false);
    setIsEpilogue(false);

    const steps = [
      { text: '[BIOS] Boot path match: SYSTEM.CNF found on cdrom0:\\\\', delay: 150 },
      { text: `[BIOS] Loading ELF target: ${config.elfName}...`, delay: 200 },
      { text: '[BIOS] Jump to executable main() entry offset 0x00100000', delay: 150 },
      { text: '[EE] TYRA_LOG: Starting \'The Seventh Vow\' on PlayStation 2...', delay: 100 },
      { text: `[EE] EngineOptions configuration: VMode=${config.videoMode}, Res=${config.resolution}, Audio=${config.audioFrequency}Hz`, delay: 100 },
      { text: '[EE] Graphics Synthesizer: Display buffer allocated in VRAM.', delay: 120 },
      { text: '[EE] TYRA_LOG: Initializing Game Subsystems for \'The Seventh Vow\'...', delay: 150 },
      { text: '[EE] IOP: Connecting to RPC services... Handshake OK.', delay: 80 },
      { text: '[IOP] audsrv: Initializing DSP audio sound buffer channels...', delay: 150 },
      { text: '[IOP] audsrv: Sound card IOP driver connected.', delay: 80 },
      { text: '[EE] TYRA_LOG: All PS2 subsystems successfully initialized. Enjoy the game!', delay: 150 },
      { text: '[EE] TYRA_LOG: Mounting disc drive filesystem... OK.', delay: 100 },
      { text: '[EE] TYRA_LOG: ScriptEngine loading external script cdrom0:\\\\SCRIPTS\\\\CHAPTER_1.TXT;1 on the fly...', delay: 150 },
      { text: '[EE] TYRA_LOG: ScriptEngine executed ZONE_INIT 0x01. Current Zone: Plains Sanctuary Gates.', delay: 120 },
      { text: '[EE] TYRA_LOG: Loaded model cdrom0:\\\\ASSETS\\\\PLAYER.OBJ;1 (14,250 vertices)', delay: 150 },
      { text: '[EE] TYRA_LOG: Bound player texture cdrom0:\\\\ASSETS\\\\PLAYER.PNG;1 into GS VRAM', delay: 100 },
    ];

    let currentIdx = 0;
    const runBootStep = () => {
      if (currentIdx >= steps.length) {
        addLog('success', '[EE] Story System Loaded. Entering Chapter 1.', 'ee');
        return;
      }
      const step = steps[currentIdx];
      
      if (step.text.includes('[IOP]') || step.text.includes('audsrv')) {
        addLog('iop', step.text, 'iop');
      } else {
        addLog(step.text.includes('TYRA_LOG') ? 'success' : 'info', step.text, 'ee');
      }

      currentIdx++;
      setTimeout(runBootStep, step.delay);
    };

    runBootStep();
  };

  const handleStop = () => {
    setIsRunning(false);
    setIsCompiling(false);
    setCompilerProgress(0);
    setActiveTab('compiler');
    addLog('warning', '[SYSTEM] Emulation halted by developer.', 'ee');
    addLog('warning', '[SYSTEM] Sound card IOP connection closed.', 'iop');
  };

  const getVowPhaseLabel = (idx: number, strength: number) => {
    const phases = ['SILENT', '1/8 DECAY', '2/8 DECAY', '3/8 DECAY', 'HALF DECAY', '5/8 DECAY', '6/8 DECAY', '7/8 DECAY', 'FULL WITNESS'];
    const basePhase = Math.min(8, Math.floor((idx / 7) * 8) + Math.floor((strength % 20) / 10));
    return phases[basePhase];
  };

  const triggerRumbleEffect = (isVowUpgrade: boolean) => {
    setIsScreenShaking(true);
    setIsRumbling(true);
    
    const attackTypeStr = isVowUpgrade ? "Vow Binding Shockwave" : "R2 Heavy Slash Strike";
    addLog('warning', `[EE] INPUT: Triggered ${attackTypeStr}. Transferring haptic SIF packet...`, 'ee');
    addLog('iop', `[IOP] iop_pad: Actuators starting (Current Scars: ${burdenScars}).`, 'iop');
    
    const duration = isVowUpgrade ? 2500 : 1500;
    let elapsed = 0;
    const intervalTime = 60;
    
    const interval = setInterval(() => {
      elapsed += intervalTime;
      if (elapsed >= duration) {
        clearInterval(interval);
        setIsRumbling(false);
        setIsScreenShaking(false);
        setRumbleLeftMotor(0);
        setRumbleRightMotor(0);
        setRumbleStutterMsg('');
        addLog('info', `[EE] INPUT: ${attackTypeStr} finished. SIF state cleared.`, 'ee');
        return;
      }
      
      let left = 100;
      let right = 90;
      let stutterType = '';
      
      // Dynamic uneven stutter proportional to burdenScars
      if (burdenScars > 0) {
        const stutterChance = Math.min(0.9, burdenScars * 0.16);
        if (Math.random() < stutterChance) {
          const roll = Math.random();
          if (roll < 0.35) {
            left = 0;
            right = 0;
            stutterType = 'MOTOR COLLAPSE (SCAR INTERRUPTION)';
          } else if (roll < 0.7) {
            left = Math.floor(Math.random() * 25);
            right = Math.floor(Math.random() * 85);
            stutterType = 'ASYMMETRIC SPASM (BODILY FATIGUE)';
          } else {
            left = Math.floor(Math.sin(elapsed * 0.12) * 45 + 50);
            right = Math.floor(Math.cos(elapsed * 0.08) * 40 + 40);
            stutterType = 'JITTER COUPLING (VOW TRANSGRESSION)';
          }
        }
      }
      
      setRumbleLeftMotor(left);
      setRumbleRightMotor(right);
      setRumbleStutterMsg(stutterType);
      
      if (stutterType && elapsed % 240 === 0) {
        addLog('warning', `[IOP] iop_pad: UNSTABLE MOTOR STUTTER: ${stutterType} [L:${left}% | R:${right}%]`, 'iop');
      } else if (elapsed % 300 === 0) {
        addLog('stdout', `[EE] DualShock2: Actuator haptics feedback (Left: ${left}%, Right: ${right}%)`, 'ee');
      }
      
      if (typeof navigator !== 'undefined' && navigator.vibrate) {
        if (left > 10 || right > 10) {
          navigator.vibrate(Math.random() > 0.5 ? [40, 20] : [30]);
        }
      }
    }, intervalTime);
  };

  const triggerHeavyAttack = () => {
    if (!isRunning || isZoneLoading || isGlitching || isEpilogue || isRumbling) return;
    triggerRumbleEffect(false);
  };

  const processChoice = (idx: number) => {
    if (!dialogueActive || isGlitching || isEpilogue) return;

    const currentChapter = GAME_CHAPTERS[currentChapterIdx];
    setSelectedChoice(idx);

    if (currentChapterIdx === 4) {
      // Act V: Spires of Manipulation - SIF Chronos Interrupt Glitch!
      setIsGlitching(true);
      setGlitchMessage("SIF CHRONOS OVERRIDE DETECTED. IMMUTABLE CANON POINT.");
      
      addLog('error', '[CRITICAL] SYSTEM OVERRIDE: SIF CHRONOS OVERRIDE ACTIVE.', 'ee');
      addLog('error', '[SYS] Red Glitch Filter engaged. CPU controller loop hijacked.', 'ee');
      addLog('error', `[NARRATIVE] Choice blocked! Lady Lys whispers: "The timeline must flow along its designated course, Xyven."`, 'ee');
      addLog('iop', 'iop_sound_core: Triggering recursive feedback echo loop.', 'iop');

      setTimeout(() => {
        setIsGlitching(false);
        addLog('success', '[NARRATIVE] SIF override bypassed. Forced action recorded.', 'ee');
        setVowStrength(v => v + 25);
        setBurdenScars(v => v + 2);
        setMaxHealthMod(v => Math.max(10, v - 15));
        setDialogueActive(false);
        triggerRumbleEffect(true);
      }, 3000);

    } else if (currentChapterIdx === 8) {
      // Act IX: Climax - Ultimate Seventh Vow Shattering!
      setIsGlitching(true);
      setGlitchMessage("TOTAL SYSTEM COLLAPSE. THE SEVENTH VOW IS SHATTERED.");
      
      addLog('error', '[CRITICAL] UNRECOVERABLE MEMORY EXCEPTION: SECTOR FALLOUT.', 'ee');
      addLog('error', '[SYS] Kernel Panic: Emotion Engine core locked in loop at 0x00000000.', 'ee');
      addLog('error', `[NARRATIVE] Xyven: "Aevior! I will sever the links! We will not be witnesses anymore!"`, 'ee');
      addLog('iop', 'iop_sound_core: Loud static pitch overload. SPU2 DMA buffer overrun.', 'iop');

      setTimeout(() => {
        setIsGlitching(false);
        setIsEpilogue(true);
        addLog('warning', '[NARRATIVE] Xyven: "Let the engine burn... we are free."', 'ee');
        addLog('success', '[SYSTEM] Emulator story ending reached. Memory registers finalized.', 'ee');
      }, 3500);

    } else {
      // Normal progression
      const choiceText = idx === 0 ? currentChapter.choiceA : currentChapter.choiceB;
      addLog('success', `[NARRATIVE] Player choice accepted: "${choiceText}"`, 'ee');
      addLog('stdout', currentChapter.successLog, 'ee');
      addLog('iop', 'iop_sound_core: Choice accepted. Loading transition ADPCM clip.', 'iop');

      // Update vow stats
      setVowStrength(v => v + 15);
      setBurdenScars(v => v + 1);
      setMaxHealthMod(v => Math.max(20, v - 5));

      setDialogueActive(false);

      // Trigger the heavy punishing rumble effect
      triggerRumbleEffect(true);
    }
  };

  const handleZoneTransition = (targetZoneIdx: number) => {
    if (isZoneLoading || isGlitching || !isRunning) return;
    setIsZoneLoading(true);
    setZoneLoadingProgress(0);
    
    addLog('warning', `[EE] ZONE TRANSITION: Moving to Zone: ${GAME_CHAPTERS[currentChapterIdx].zones[targetZoneIdx]}`, 'ee');
    addLog('warning', `[EE] MEMORY: SIF DMA flushing old level sector assets (Purging 32MB Main RAM Heap)...`, 'ee');
    addLog('iop', '[IOP] audsrv: Purging audio channel sound caches.', 'iop');
    
    const startSector = 14500 + currentChapterIdx * 5000 + targetZoneIdx * 800;
    setActiveDvdSector(startSector);

    let progress = 0;
    const interval = setInterval(() => {
      progress += 10;
      setZoneLoadingProgress(progress);
      setActiveDvdSector(startSector + Math.floor(progress * 4.2));

      if (progress % 30 === 0) {
        addLog('stdout', `[EE] DVD Read: Streaming sector ${startSector + Math.floor(progress * 4.2)} | Speed: ${dvdReadSpeed}`, 'ee');
      }

      if (progress >= 100) {
        clearInterval(interval);
        setIsZoneLoading(false);
        setActiveZoneIdx(targetZoneIdx);
        
        addLog('success', `[EE] ZONE LOADED: Successfully initialized ${GAME_CHAPTERS[currentChapterIdx].zones[targetZoneIdx]}`, 'ee');
        addLog('success', `[EE] MEMORY: Loaded model & texture pointers into Emotion Engine skeleton structure (<4KB)`, 'ee');
        addLog('iop', `[IOP] audsrv: Sound core buffer cached successfully for Zone ${targetZoneIdx + 1}.`, 'iop');
        
        setStats(prev => ({
          ...prev,
          vramAlloc: Number((1.1 + Math.random() * 0.15).toFixed(2)),
          ramAlloc: Number((11.5 + Math.random() * 0.8).toFixed(1)),
        }));
      }
    }, 150);
  };

  const handleNextChapter = () => {
    if (isEpilogue || isGlitching) return;

    if (currentChapterIdx < GAME_CHAPTERS.length - 1) {
      const nextIdx = currentChapterIdx + 1;
      
      setIsZoneLoading(true);
      setZoneLoadingProgress(0);
      
      addLog('info', '=======================================================', 'ee');
      addLog('info', ` [CHAPTER] Transitioning to Chapter ${nextIdx + 1}: loading external scripts...`, 'ee');
      addLog('warning', ` [MEMORY] Releasing immutable buffers. Purging texture registers in GS VRAM.`, 'ee');
      addLog('iop', `iop_sound_core: Loading next chapter sound track cdrom0:\\\\AUDIO\\\\TRACK_${nextIdx + 1}.WAV;1`, 'iop');
      addLog('info', '=======================================================', 'ee');

      const startSector = 14500 + nextIdx * 5000;
      setActiveDvdSector(startSector);

      let progress = 0;
      const interval = setInterval(() => {
        progress += 8;
        setZoneLoadingProgress(progress);
        setActiveDvdSector(startSector + Math.floor(progress * 6.5));

        if (progress >= 100) {
          clearInterval(interval);
          setIsZoneLoading(false);
          setCurrentChapterIdx(nextIdx);
          setActiveZoneIdx(0);
          setSelectedChoice(null);
          setDialogueActive(true);
          
          addLog('success', ` [CHAPTER] Loaded Chapter script: ${GAME_CHAPTERS[nextIdx].scriptFile}`, 'ee');
          addLog('success', ` [REGION] Bound Region: ${GAME_CHAPTERS[nextIdx].region}`, 'ee');
          addLog('success', ` [REGION] dominantSin Filter: ${GAME_CHAPTERS[nextIdx].sin}`, 'ee');
          addLog('iop', `iop_sound_core: Streaming ADPCM background tracks. SPU2 ready.`, 'iop');
        }
      }, 150);

    } else {
      addLog('success', '[CHAPTER] Story complete! Witnessed the eternal cycle.', 'ee');
    }
  };

  return (
    <div className="bg-[#0b0d10] border border-[#22272e] rounded-lg shadow-2xl p-4 space-y-4">
      {/* Header and Controls */}
      <div className="flex flex-col md:flex-row justify-between items-start md:items-center gap-3 border-b border-[#22272e] pb-3">
        <div className="flex items-center gap-2">
          <Cpu className={`w-5 h-5 ${isRunning ? 'text-emerald-400 animate-pulse' : 'text-blue-500'}`} />
          <div>
            <h3 className="font-bold text-gray-200 text-xs font-mono uppercase tracking-wider flex items-center gap-1.5">
              PS2 Emulator Devkit Simulator
              {isRunning && <span className="text-[9px] bg-emerald-500/10 text-emerald-400 px-1.5 py-0.5 rounded font-mono border border-emerald-500/20 uppercase tracking-tight font-bold animate-pulse">Running</span>}
            </h3>
            <p className="text-[10px] text-gray-500 font-mono">Simulating Emotion Engine (EE) CPU and IOP sound registers</p>
          </div>
        </div>

        <div className="flex gap-2 w-full md:w-auto">
          {!isRunning && !isCompiling ? (
            <button
              onClick={handleCompileAndBoot}
              className="flex-1 md:flex-none flex items-center justify-center gap-2 px-4 py-2 rounded bg-blue-600 hover:bg-blue-700 text-white font-bold font-mono text-[11px] uppercase transition-all shadow-md shadow-blue-950 active:scale-95"
            >
              <Play className="w-3.5 h-3.5 fill-current" />
              Compile & Boot Game
            </button>
          ) : (
            <button
              onClick={handleStop}
              className="flex-1 md:flex-none flex items-center justify-center gap-2 px-4 py-2 rounded bg-red-600/10 hover:bg-red-600/20 text-red-400 border border-red-500/20 font-bold font-mono text-[11px] uppercase transition-all active:scale-95"
            >
              <RotateCcw className="w-3.5 h-3.5" />
              Stop Emulator
            </button>
          )}
        </div>
      </div>

      {/* Live Hardware Stats Panel */}
      <div className="grid grid-cols-2 sm:grid-cols-5 gap-2 bg-[#12161b] p-3 rounded border border-[#22272e]">
        <div className="bg-[#0b0d10] p-2 rounded border border-[#1e242c]">
          <span className="block text-[9px] text-gray-500 uppercase font-bold tracking-tight">EE Frame Rate</span>
          <span className={`font-mono text-base font-bold ${isRunning ? 'text-emerald-400' : 'text-gray-600'}`}>
            {isRunning ? `${stats.fps}.00` : '00.00'} <span className="text-[10px] text-gray-500">FPS</span>
          </span>
        </div>
        <div className="bg-[#0b0d10] p-2 rounded border border-[#1e242c]">
          <span className="block text-[9px] text-gray-500 uppercase font-bold tracking-tight">GS Draw Calls</span>
          <span className={`font-mono text-base font-bold ${isRunning ? 'text-cyan-400' : 'text-gray-600'}`}>
            {isRunning ? stats.drawCalls : '0'} <span className="text-[10px] text-gray-500">Calls</span>
          </span>
        </div>
        <div className="bg-[#0b0d10] p-2 rounded border border-[#1e242c]">
          <span className="block text-[9px] text-gray-500 uppercase font-bold tracking-tight">GS VRAM Used</span>
          <span className={`font-mono text-base font-bold ${isRunning ? 'text-amber-400' : 'text-gray-600'}`}>
            {isRunning ? `${stats.vramAlloc}` : '0.00'} <span className="text-[10px] text-gray-500">/ 4MB</span>
          </span>
        </div>
        <div className="bg-[#0b0d10] p-2 rounded border border-[#1e242c]">
          <span className="block text-[9px] text-gray-500 uppercase font-bold tracking-tight">EE System RAM</span>
          <span className={`font-mono text-base font-bold ${isRunning ? 'text-blue-400' : 'text-gray-600'}`}>
            {isRunning ? `${stats.ramAlloc}` : '0.00'} <span className="text-[10px] text-gray-500">/ 32MB</span>
          </span>
        </div>
        <div className="bg-[#0b0d10] p-2 rounded border border-[#1e242c] col-span-2 sm:col-span-1">
          <span className="block text-[9px] text-gray-500 uppercase font-bold tracking-tight">SPU2 IOP RAM</span>
          <span className={`font-mono text-base font-bold ${isRunning ? 'text-pink-400' : 'text-gray-600'}`}>
            {isRunning ? `${stats.iopAlloc}` : '0.00'} <span className="text-[10px] text-gray-500">/ 2MB</span>
          </span>
        </div>
      </div>

      {/* Simulator Interface Tabs */}
      <div className="flex flex-col h-[340px] md:h-[380px]">
        {/* Tab Headers */}
        <div className="flex border-b border-[#22272e] bg-[#12161b] rounded-t-lg overflow-hidden text-[10px] font-mono select-none">
          {isRunning && (
            <button
              onClick={() => setActiveTab('screen')}
              className={`flex items-center gap-1.5 px-4 py-2 border-r border-[#22272e] transition-all ${
                activeTab === 'screen'
                  ? 'bg-[#0b0d10] text-blue-400 font-bold border-t-2 border-t-blue-500'
                  : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
              }`}
            >
              <Tv className="w-3.5 h-3.5 text-blue-400 animate-pulse" />
              <span>Live CRT Screen</span>
            </button>
          )}
          <button
            onClick={() => setActiveTab('compiler')}
            className={`flex items-center gap-1.5 px-4 py-2 border-r border-[#22272e] transition-all ${
              activeTab === 'compiler'
                ? 'bg-[#0b0d10] text-blue-400 font-bold border-t-2 border-t-blue-500'
                : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
            }`}
          >
            <Terminal className="w-3.5 h-3.5" />
            <span>GCC Compiler</span>
          </button>
          <button
            onClick={() => setActiveTab('ee')}
            className={`flex items-center gap-1.5 px-4 py-2 border-r border-[#22272e] transition-all ${
              activeTab === 'ee'
                ? 'bg-[#0b0d10] text-emerald-400 font-bold border-t-2 border-t-emerald-500'
                : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
            }`}
          >
            <Cpu className="w-3.5 h-3.5" />
            <span>Emotion Engine (EE) Log</span>
          </button>
          <button
            onClick={() => setActiveTab('iop')}
            className={`flex items-center gap-1.5 px-4 py-2 border-r border-[#22272e] transition-all ${
              activeTab === 'iop'
                ? 'bg-[#0b0d10] text-pink-400 font-bold border-t-2 border-t-pink-500'
                : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
            }`}
          >
            <Gamepad className="w-3.5 h-3.5" />
            <span>IOP Sound Core</span>
          </button>
          <button
            onClick={() => setActiveTab('vram')}
            className={`flex items-center gap-1.5 px-4 py-2 border-r border-[#22272e] transition-all ${
              activeTab === 'vram'
                ? 'bg-[#0b0d10] text-amber-400 font-bold border-t-2 border-t-amber-500'
                : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
            }`}
          >
            <Layers className="w-3.5 h-3.5" />
            <span>GS VRAM Matrix</span>
          </button>
          <button
            onClick={() => setActiveTab('dvd')}
            className={`flex items-center gap-1.5 px-4 py-2 transition-all ${
              activeTab === 'dvd'
                ? 'bg-[#0b0d10] text-blue-400 font-bold border-t-2 border-t-blue-500'
                : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
            }`}
          >
            <Activity className="w-3.5 h-3.5 text-blue-400 animate-pulse" />
            <span>DVD Disc Streamer</span>
          </button>
        </div>

        {/* Tab Body */}
        <div className="flex-1 bg-[#0b0d10] p-3 border-x border-b border-[#22272e] overflow-y-auto font-mono text-[11px] leading-relaxed rounded-b-lg select-text text-gray-400">
          
          {/* Active CRT Game Screen simulation */}
          {activeTab === 'screen' && isRunning && (
            <div className="grid grid-cols-1 lg:grid-cols-12 gap-4 h-full min-h-0 select-none">
              {/* Retro Monitor display */}
              <div 
                className={`lg:col-span-8 flex flex-col relative bg-black border-4 rounded-xl overflow-hidden shadow-[inset_0_0_25px_rgba(0,0,0,0.95)] max-h-[340px] lg:max-h-none transition-all duration-75 ${isScreenShaking ? 'border-red-600 shadow-[0_0_30px_rgba(255,50,0,0.4)]' : 'border-[#3c4755]'}`}
                style={isScreenShaking ? { transform: `translate(${(Math.random() - 0.5) * 6}px, ${(Math.random() - 0.5) * 6}px)` } : undefined}
              >
                {isEpilogue ? (
                  /* Epilogue credits / final cinematic sequences */
                  <div className="flex-1 flex flex-col items-center justify-center p-6 text-center bg-black font-mono space-y-4 overflow-y-auto">
                    <Skull className="w-8 h-8 text-red-500 animate-pulse shrink-0" />
                    <div className="space-y-3">
                      <p className="text-gray-200 text-xs font-bold uppercase tracking-widest text-red-500">
                        === EPILOGUE: THE SEVENTH VOW ===
                      </p>
                      <div className="text-gray-400 text-[10.5px] max-w-md mx-auto space-y-2 leading-relaxed leading-normal text-left">
                        <p className="border-l border-red-500/50 pl-2">
                          * Historical records fading in: <span className="text-gray-200 font-bold">"Xyven Tyr, The Great Betrayer. There is no monument, no burial marker, no hero's song."</span>
                        </p>
                        <p className="border-l border-blue-500/50 pl-2">
                          * Aevior survived... carrying the shattered shield and a silent memory of the timeline. He kneels on the snow-swept slopes.
                        </p>
                        <p className="border-l border-emerald-500/50 pl-2">
                          * Imigh looks out from the floating gears of Elyndra's clockwork sky, laughing softly: <span className="text-emerald-400">"You thought you were the player? You were only allowed to witness."</span>
                        </p>
                      </div>
                    </div>
                    <button
                      onClick={() => bootPS2()}
                      className="px-3 py-1 bg-red-950/40 border border-red-700/50 hover:bg-red-900/60 text-red-400 rounded text-[9.5px] uppercase font-bold tracking-tight transition-all active:scale-95"
                    >
                      Reset Memories Loop (Restart)
                    </button>
                  </div>
                ) : (
                  /* Live Game Display */
                  <div className="flex-1 flex flex-col justify-between relative">
                    {/* Game Canvas rendering the 3D grid and sword */}
                    <canvas
                      ref={canvasRef}
                      width={440}
                      height={200}
                      className="absolute inset-0 w-full h-full object-cover rounded pointer-events-none"
                    />

                    {/* Nostalgic Zone Loading Screen Overlay */}
                    {isZoneLoading && (
                      <div className="absolute inset-0 bg-[#06080b] flex flex-col justify-center items-center p-6 text-center z-30 font-mono space-y-4">
                        <div className="space-y-1">
                          <p className="text-gray-100 text-xs font-black tracking-widest uppercase animate-pulse">
                            NOW LOADING ZONE...
                          </p>
                          <p className="text-[9px] text-gray-400">
                            Zone {activeZoneIdx + 1}: <span className="text-cyan-400 font-bold">{GAME_CHAPTERS[currentChapterIdx].zones[activeZoneIdx]}</span>
                          </p>
                        </div>

                        {/* Progress Bar */}
                        <div className="w-48 h-2.5 bg-gray-900 border border-gray-700 rounded-full overflow-hidden p-0.5">
                          <div
                            className="h-full bg-cyan-500 rounded-full transition-all duration-150"
                            style={{ width: `${zoneLoadingProgress}%` }}
                          />
                        </div>

                        {/* Dynamic Streaming Logs */}
                        <div className="text-[8px] text-gray-500 space-y-0.5 text-left w-60 max-w-full border-t border-gray-800 pt-2 font-mono">
                          <div className="flex justify-between">
                            <span>Optical Device:</span>
                            <span className="text-gray-300 font-bold">cdrom0:\\\\LBA {activeDvdSector}</span>
                          </div>
                          <div className="flex justify-between">
                            <span>SIF DMA Status:</span>
                            <span className="text-emerald-400 font-bold uppercase">PURGING OLD HEAP</span>
                          </div>
                          <div className="flex justify-between">
                            <span>VRAM Page Allocator:</span>
                            <span className="text-amber-500 font-bold uppercase">FLUSHING GS REGISTERS</span>
                          </div>
                        </div>
                      </div>
                    )}

                    {/* HUD display overlays (SMT: Nocturne Stylized Visual Despair Theme) */}
                    <div className="p-3.5 flex justify-between items-start z-10 w-full select-none">
                      
                      {/* SMT: Nocturne Kagutsuchi Dial: Vow Phase Tracker */}
                      <div className="flex items-center gap-2.5 bg-black/90 border border-[#00ffff]/40 p-2 text-white skew-x-[-10deg] backdrop-blur-md shadow-[0_0_15px_rgba(0,255,255,0.15)] rounded-sm">
                        <div className="relative w-9 h-9 flex items-center justify-center shrink-0">
                          {/* Outer rotating wheel with markings */}
                          <svg className="absolute inset-0 w-full h-full rotate-[45deg] animate-[spin_16s_linear_infinite]" viewBox="0 0 36 36">
                            <circle cx="18" cy="18" r="15" fill="none" stroke="#161b22" strokeWidth="2" />
                            <circle cx="18" cy="18" r="15" fill="none" stroke="#00ffff" strokeWidth="1.5" strokeDasharray="3, 5" />
                          </svg>
                          
                          {/* Phase Center indicator */}
                          <div className={`w-5 h-5 rounded-full flex items-center justify-center text-[8.5px] font-black tracking-tight ${burdenScars > 4 ? 'bg-red-600 text-black animate-pulse shadow-[0_0_10px_#ef4444]' : 'bg-[#ffff00] text-black shadow-[0_0_8px_#ffff00]'}`}>
                            {currentChapterIdx + 1}
                          </div>
                        </div>
                        
                        <div className="font-mono text-[8px] tracking-widest text-left leading-tight">
                          <div className="text-gray-400 font-bold uppercase">ALIGNMENT</div>
                          <div className="text-[#ffff00] font-black text-[9px] uppercase animate-pulse">
                            {getVowPhaseLabel(currentChapterIdx, vowStrength)}
                          </div>
                          <div className="text-gray-500 text-[6.5px]">TEMPORAL SYNC: {100 - burdenScars * 12}%</div>
                        </div>
                      </div>

                      {/* SMT Slanted Character Stats Box */}
                      <div className="bg-black/95 border-y-2 border-r-2 border-l-8 border-[#00ffff] border-l-[#ffff00] p-2 text-white skew-x-[-12deg] backdrop-blur-md shadow-[4px_4px_0px_#000] text-right min-w-[130px]">
                        <div className="font-sans font-black text-[9px] text-[#00ffff] tracking-widest uppercase mb-1 flex items-center justify-end gap-1.5">
                          XYVEN <span className="text-[8px] text-red-500 font-bold bg-red-950/40 border border-red-900/50 px-1">LV.{12 + currentChapterIdx * 6}</span>
                        </div>
                        
                        <div className="space-y-1 font-mono text-[8px] tracking-tight">
                          {/* Slanted HP bar */}
                          <div className="flex justify-between items-center gap-2">
                            <span className="text-gray-400 font-bold">HP</span>
                            <div className="w-16 h-1.5 bg-gray-900 border border-gray-700 overflow-hidden relative flex items-center">
                              <div
                                className={`h-full transition-all duration-300 ${maxHealthMod < 50 ? 'bg-red-600' : 'bg-emerald-400'}`}
                                style={{ width: `${maxHealthMod}%` }}
                              />
                            </div>
                            <span className="font-bold text-[#ffff00] min-w-[18px]">{maxHealthMod}</span>
                          </div>

                          {/* Vow strength bar */}
                          <div className="flex justify-between items-center gap-2">
                            <span className="text-gray-400 font-bold">VOW</span>
                            <div className="w-16 h-1.5 bg-gray-900 border border-gray-700 overflow-hidden relative flex items-center">
                              <div
                                className="h-full bg-cyan-400 transition-all duration-300"
                                style={{ width: `${Math.min(100, vowStrength)}%` }}
                              />
                            </div>
                            <span className="font-bold text-cyan-400 min-w-[18px]">{vowStrength}</span>
                          </div>

                          {/* Scar decaying metadata */}
                          <div className="flex justify-between text-[7px] border-t border-gray-900 pt-1 mt-1 font-bold">
                            <span className="text-purple-400 uppercase">SCARS: {burdenScars.toString().padStart(2, '0')}</span>
                            <span className={`${burdenScars > 3 ? 'text-red-500 animate-pulse' : 'text-gray-500'} uppercase`}>
                              {burdenScars > 4 ? '[CRITICAL BODY]' : burdenScars > 2 ? '[DECAYING]' : '[STABLE]'}
                            </span>
                          </div>
                        </div>
                      </div>

                    </div>
 
                    {/* Red Glitch Intercept Warnings */}
                    {isGlitching && (
                      <div className="absolute inset-0 bg-red-950/80 flex flex-col items-center justify-center text-center p-4 z-20 font-mono space-y-2 animate-pulse">
                        <ShieldAlert className="w-10 h-10 text-red-500" />
                        <h4 className="text-red-400 font-black tracking-widest text-[11px] uppercase">
                          [CRITICAL ERROR] CHRONOS OVERRIDE
                        </h4>
                        <p className="text-gray-200 text-[10px] uppercase font-bold tracking-tight">
                          Witness Mode Active. Input Intercepted.
                        </p>
                        <p className="text-red-400 text-[9px] border-t border-red-700/50 pt-1 font-semibold">
                          Imigh: "He never belonged to you. You were only allowed to watch."
                        </p>
                      </div>
                    )}
 
                    {/* SMT: Nocturne Stylized Lower Subtitle Dialogue Panel */}
                    <div className="p-3 mt-auto z-10 w-full select-none">
                      <div className="bg-black border-2 border-[#00ffff] p-3 space-y-2 relative shadow-[4px_4px_0px_rgba(0,0,0,1)] rounded-sm">
                        
                        {/* Speaker Name Badge */}
                        <div className="absolute -top-3 left-4 bg-[#ffff00] text-black text-[8px] font-black px-3.5 py-0.5 uppercase tracking-widest border border-black skew-x-[-12deg] shadow-[2px_2px_0px_#000]">
                          {GAME_CHAPTERS[currentChapterIdx].speaker}
                        </div>
                        
                        <div className="flex justify-between items-center border-b border-gray-900 pb-1.5 pt-1">
                          <span className="text-[7.5px] text-gray-500 tracking-wider font-mono">
                            EMOTION ENGINE SCRIPT PARSER // {GAME_CHAPTERS[currentChapterIdx].vowType}
                          </span>
                          <span className="text-[7.5px] text-[#ffff00] font-black tracking-widest animate-pulse font-mono">
                            PRESS CROSS (A) / CIRCLE (B)
                          </span>
                        </div>
                        
                        <p className="text-[#00ffff] text-[10px] leading-relaxed min-h-[28px] font-mono font-bold tracking-tight">
                          {typedLine}
                        </p>
 
                        {/* Choices visual buttons */}
                        {dialogueActive && (
                          <div className="grid grid-cols-2 gap-2 pt-1.5 font-mono">
                            <button
                              onClick={() => processChoice(0)}
                              className={`py-1.5 px-2 text-[9px] font-black uppercase transition-all flex items-center justify-center gap-1.5 border-2 text-left ${
                                selectedChoice === 0
                                  ? 'bg-[#ffff00] text-black border-white shadow-none'
                                  : 'bg-black text-[#00ffff] border-[#00ffff] hover:bg-[#00ffff] hover:text-black hover:border-white shadow-[2px_2px_0px_rgba(0,255,255,0.2)]'
                              }`}
                            >
                              <span className="w-3.5 h-3.5 bg-blue-600 text-white rounded-full text-[8px] font-black flex items-center justify-center shrink-0 border border-black">X</span>
                              {GAME_CHAPTERS[currentChapterIdx].choiceA}
                            </button>
                            <button
                              onClick={() => processChoice(1)}
                              className={`py-1.5 px-2 text-[9px] font-black uppercase transition-all flex items-center justify-center gap-1.5 border-2 text-left ${
                                selectedChoice === 1
                                  ? 'bg-[#ffff00] text-black border-white shadow-none'
                                  : 'bg-black text-[#00ffff] border-[#00ffff] hover:bg-[#00ffff] hover:text-black hover:border-white shadow-[2px_2px_0px_rgba(0,255,255,0.2)]'
                              }`}
                            >
                              <span className="w-3.5 h-3.5 bg-purple-600 text-white rounded-full text-[8px] font-black flex items-center justify-center shrink-0 border border-black">O</span>
                              {GAME_CHAPTERS[currentChapterIdx].choiceB}
                            </button>
                          </div>
                        )}
 
                        {!dialogueActive && (
                          <div className="flex justify-between items-center pt-1.5 text-[9px] font-mono">
                            <span className="text-[#ffff00] font-black flex items-center gap-1 uppercase tracking-widest animate-pulse">
                              ▶ DECISION RESOLVED
                            </span>
                            {currentChapterIdx < GAME_CHAPTERS.length - 1 ? (
                              <button
                                onClick={handleNextChapter}
                                className="px-3 py-1 bg-[#00ffff] hover:bg-[#ffff00] text-black font-black text-[8.5px] uppercase tracking-widest border border-black transition-all active:scale-95 shadow-[2px_2px_0px_#000]"
                              >
                                PROGRESS CHAPTER (Δ)
                              </button>
                            ) : (
                              <span className="text-red-500 font-black uppercase tracking-widest animate-pulse">
                                STORY RESOLVED
                              </span>
                            )}
                          </div>
                        )}
                      </div>
                    </div>
                  </div>
                )}
              </div>

              {/* Gamepad Control Interface */}
              <div className="lg:col-span-4 flex flex-col justify-between bg-[#12161b] border border-[#22272e] rounded-xl p-3 space-y-3 font-mono">
                <div className="space-y-1.5 border-b border-[#22272e] pb-2">
                  <span className="text-[9.5px] font-bold text-gray-300 uppercase tracking-wider flex items-center gap-1">
                    <Gamepad className="w-3.5 h-3.5 text-blue-400" />
                    DualShock 2 Pad 1
                  </span>
                  <p className="text-[8px] text-gray-500">Click controller pads to operate simulated hardware interrupts</p>
                </div>

                {/* Simulated Gamepad grid */}
                <div className="flex-1 flex flex-col justify-center space-y-4">
                  {/* Joystick Camera Orbit control */}
                  <div className="bg-[#0b0d10] border border-[#22272e] p-2.5 rounded-lg flex flex-col items-center gap-2">
                    <span className="text-[8px] text-gray-400 uppercase font-bold tracking-tight">Right Stick (Camera Orbit)</span>
                    <div className="flex gap-2">
                      <button
                        onClick={() => setCameraYaw(y => y - 0.4)}
                        className="px-2 py-1 bg-[#161b22] hover:bg-[#21262d] border border-[#30363d] rounded text-[8.5px] font-bold text-gray-300 active:scale-90 transition-all"
                        title="Orbit Camera Left"
                      >
                        ◀ L
                      </button>
                      <button
                        onClick={() => setCameraYaw(y => y + 0.4)}
                        className="px-2 py-1 bg-[#161b22] hover:bg-[#21262d] border border-[#30363d] rounded text-[8.5px] font-bold text-gray-300 active:scale-90 transition-all"
                        title="Orbit Camera Right"
                      >
                        R ▶
                      </button>
                    </div>
                  </div>

                  {/* Zone Navigator Controller */}
                  <div className="bg-[#0b0d10] border border-[#22272e] p-2 rounded-lg flex flex-col gap-1.5">
                    <span className="text-[8px] text-gray-400 uppercase font-bold tracking-tight block border-b border-[#22272e] pb-1">Zone Gateways (The Zone Solution)</span>
                    <div className="grid grid-cols-3 gap-1">
                      {GAME_CHAPTERS[currentChapterIdx].zones.map((zone, idx) => (
                        <button
                          key={idx}
                          onClick={() => handleZoneTransition(idx)}
                          disabled={isZoneLoading || isGlitching || !isRunning}
                          className={`py-1 px-1 rounded text-[8px] font-bold uppercase transition-all border text-center ${
                            activeZoneIdx === idx
                              ? 'bg-cyan-600/20 text-cyan-400 border-cyan-500'
                              : 'bg-[#12161b]/80 text-gray-400 border-[#22272e] hover:bg-[#1a2027] hover:border-gray-500 disabled:opacity-40'
                          }`}
                          title={`Gate to ${zone}`}
                        >
                          Zone {idx + 1}
                        </button>
                      ))}
                    </div>
                    <div className="flex justify-between text-[7.5px] text-gray-500 font-mono">
                      <button
                        onClick={() => {
                          if (activeZoneIdx > 0) handleZoneTransition(activeZoneIdx - 1);
                        }}
                        disabled={isZoneLoading || isGlitching || !isRunning || activeZoneIdx === 0}
                        className="hover:text-gray-300 disabled:opacity-40 uppercase font-bold"
                      >
                        [L1] Prev
                      </button>
                      <button
                        onClick={() => {
                          if (activeZoneIdx < 2) handleZoneTransition(activeZoneIdx + 1);
                        }}
                        disabled={isZoneLoading || isGlitching || !isRunning || activeZoneIdx === 2}
                        className="hover:text-gray-300 disabled:opacity-40 uppercase font-bold"
                      >
                        [R1] Next
                      </button>
                    </div>
                  </div>

                  {/* DualShock 2 Actuator Registers & Physical Haptics Dashboard */}
                  <div className="bg-[#0b0d10] border border-[#22272e] p-2.5 rounded-lg space-y-2.5">
                    <div className="flex justify-between items-center border-b border-[#22272e] pb-1">
                      <span className="text-[8px] text-[#00ffff] uppercase font-bold tracking-tight">IOP Controller Actuator Regs (0x1F24)</span>
                      <span className={`w-1.5 h-1.5 rounded-full ${isRumbling ? 'bg-red-500 animate-ping' : 'bg-green-500'}`} />
                    </div>

                    <div className="space-y-2 text-[8px] font-mono">
                      {/* Left Motor (Heavy weights, 15Hz) */}
                      <div>
                        <div className="flex justify-between font-bold text-gray-300">
                          <span>Left Motor Actuator (Low Freq Heavy weight)</span>
                          <span className={rumbleLeftMotor > 0 ? 'text-[#ffff00]' : 'text-gray-500'}>
                            {rumbleLeftMotor}%
                          </span>
                        </div>
                        <div className="h-1.5 bg-[#161b22] rounded overflow-hidden mt-0.5 border border-[#22272e]">
                          <div 
                            className="h-full bg-red-500 transition-all duration-75" 
                            style={{ width: `${rumbleLeftMotor}%` }} 
                          />
                        </div>
                      </div>

                      {/* Right Motor (Light weights, 120Hz) */}
                      <div>
                        <div className="flex justify-between font-bold text-gray-300">
                          <span>Right Motor Actuator (High Freq Jitter weight)</span>
                          <span className={rumbleRightMotor > 0 ? 'text-cyan-400' : 'text-gray-500'}>
                            {rumbleRightMotor}%
                          </span>
                        </div>
                        <div className="h-1.5 bg-[#161b22] rounded overflow-hidden mt-0.5 border border-[#22272e]">
                          <div 
                            className="h-full bg-cyan-400 transition-all duration-75" 
                            style={{ width: `${rumbleRightMotor}%` }} 
                          />
                        </div>
                      </div>

                      {/* Dysrhythmia & Stutter warning proportional to scars */}
                      <div className="bg-[#12161b] p-1.5 rounded border border-[#22272e] space-y-1">
                        <div className="flex justify-between font-bold text-[7.5px]">
                          <span className="text-gray-400 uppercase">Haptic Rhythm Sync:</span>
                          {burdenScars > 0 ? (
                            <span className="text-purple-400 animate-pulse">
                              UNSTABLE DYSRHYTHMIA ({Math.min(90, burdenScars * 16)}%)
                            </span>
                          ) : (
                            <span className="text-emerald-400">COHERENT SYNC</span>
                          )}
                        </div>
                        {isRumbling && rumbleStutterMsg && (
                          <div className="text-[7px] text-red-400 font-bold uppercase animate-pulse border-t border-red-950/40 pt-1 flex items-center gap-1">
                            <span>⚠ EFFECT:</span>
                            <span>{rumbleStutterMsg}</span>
                          </div>
                        )}
                      </div>
                    </div>
                  </div>
                </div>

                {/* Quick actions panel with Manual Heavy Attack trigger */}
                <div className="border-t border-[#22272e] pt-2 flex flex-col gap-2">
                  <div className="flex justify-between items-center">
                    <span className="text-[8px] text-gray-500 uppercase font-bold tracking-tight">Active Mappings:</span>
                    <span className="text-[7.5px] text-[#ffff00] font-bold uppercase font-mono">SIF PAD PORT 1</span>
                  </div>

                  {/* Manual trigger for Heavy Attack */}
                  <button
                    onClick={triggerHeavyAttack}
                    disabled={isRumbling || !isRunning || isZoneLoading}
                    className={`py-2 px-2 border-2 text-[9px] font-black uppercase transition-all flex items-center justify-center gap-2 select-none active:scale-95 ${
                      isRumbling 
                        ? 'bg-red-950/30 border-red-700/50 text-red-500' 
                        : 'bg-black text-[#00ffff] border-[#00ffff] hover:bg-[#00ffff] hover:text-black hover:border-white shadow-[0_0_10px_rgba(0,255,255,0.15)] disabled:opacity-40'
                    }`}
                  >
                    <span className="bg-[#444] text-white px-1.5 py-0.5 rounded text-[8px] border border-black font-sans shadow-[1px_1px_0px_#000]">R2</span>
                    {isRumbling ? 'Vibrating / Stuttering...' : 'EXECUTE HEAVY ATTACK (SWORD SLASH)'}
                  </button>

                  <div className="grid grid-cols-2 gap-1.5 text-[8.5px]">
                    <div className="bg-[#0b0d10] p-1 rounded border border-[#22272e] flex items-center gap-1 text-gray-500">
                      <span className="w-3.5 h-3.5 bg-blue-600 text-white rounded-full text-[8px] font-black flex items-center justify-center shrink-0 border border-black">X</span>
                      <span>Option A</span>
                    </div>
                    <div className="bg-[#0b0d10] p-1 rounded border border-[#22272e] flex items-center gap-1 text-gray-500">
                      <span className="w-3.5 h-3.5 bg-purple-600 text-white rounded-full text-[8px] font-black flex items-center justify-center shrink-0 border border-black">O</span>
                      <span>Option B</span>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          )}

          {activeTab === 'compiler' && (
            <div className="space-y-1">
              {isCompiling && (
                <div className="mb-3 bg-blue-950/20 border border-blue-500/30 rounded p-2.5 flex items-center justify-between">
                  <div className="flex items-center gap-2">
                    <span className="w-2 h-2 rounded-full bg-blue-500 animate-ping" />
                    <span className="text-blue-400 text-[10px] uppercase font-bold tracking-wider">Compiling Sources with mips64r5900el-ps2-elf-g++...</span>
                  </div>
                  <span className="text-blue-400 text-[10px] font-bold">{compilerProgress}%</span>
                </div>
              )}
              {compilerLogs.map(log => (
                <div key={log.id} className="flex gap-2 py-0.5 border-b border-[#141a21]/40 last:border-0">
                  <span className="text-gray-600 shrink-0">[{log.timestamp}]</span>
                  <span className={`
                    ${log.type === 'success' ? 'text-emerald-400' : ''}
                    ${log.type === 'error' ? 'text-red-400 font-bold' : ''}
                    ${log.type === 'warning' ? 'text-amber-400' : ''}
                    ${log.type === 'info' ? 'text-gray-300' : ''}
                  `}>
                    {log.text}
                  </span>
                </div>
              ))}
              <div ref={compilerLogsEndRef} />
            </div>
          )}

          {activeTab === 'ee' && (
            <div className="space-y-1">
              {eeLogs.map(log => (
                <div key={log.id} className="flex gap-2 py-0.5 border-b border-[#141a21]/40 last:border-0">
                  <span className="text-gray-600 shrink-0">[{log.timestamp}]</span>
                  <span className={`
                    ${log.type === 'success' ? 'text-emerald-400 font-semibold' : ''}
                    ${log.type === 'stdout' ? 'text-cyan-300' : ''}
                    ${log.type === 'error' ? 'text-red-400 font-bold' : ''}
                    ${log.type === 'warning' ? 'text-amber-400' : ''}
                    ${log.type === 'info' ? 'text-gray-300' : ''}
                  `}>
                    {log.text}
                  </span>
                </div>
              ))}
              <div ref={eeLogsEndRef} />
            </div>
          )}

          {activeTab === 'iop' && (
            <div className="space-y-1">
              {iopLogs.map(log => (
                <div key={log.id} className="flex gap-2 py-0.5 border-b border-[#141a21]/40 last:border-0">
                  <span className="text-gray-600 shrink-0">[{log.timestamp}]</span>
                  <span className={`
                    ${log.type === 'iop' ? 'text-pink-400' : ''}
                    ${log.type === 'info' ? 'text-gray-400' : ''}
                    ${log.type === 'success' ? 'text-emerald-400' : ''}
                  `}>
                    {log.text}
                  </span>
                </div>
              ))}
              <div ref={iopLogsEndRef} />
            </div>
          )}

          {activeTab === 'vram' && (
            <div className="space-y-4">
              <div>
                <span className="block text-[10px] text-gray-500 uppercase font-bold tracking-tight mb-2">Graphics Synthesizer VRAM Page Map (4.0MB Embedded RAM)</span>
                <div className="grid grid-cols-16 gap-1 border border-[#22272e] p-2 bg-[#090b0e] rounded">
                  {Array.from({ length: 128 }).map((_, i) => {
                    let cellColor = 'bg-[#181d24]'; // empty
                    let tooltip = 'Free VRAM page';
                    
                    if (isRunning) {
                      if (i < 32) {
                        cellColor = 'bg-blue-600/60 border border-blue-500/30';
                        tooltip = 'Frame buffer page (640x448x32bit color)';
                      } else if (i < 48) {
                        cellColor = 'bg-cyan-600/60 border border-cyan-500/30';
                        tooltip = 'Z-buffer page (Depth buffer page)';
                      } else if (i >= 80 && i < 112) {
                        cellColor = 'bg-amber-600/60 border border-amber-500/30 animate-pulse';
                        tooltip = 'Bound texture page (PLAYER.PNG, HUD.PNG)';
                      }
                    }

                    return (
                      <div
                        key={i}
                        className={`h-4 rounded-sm transition-all hover:scale-110 ${cellColor}`}
                        title={tooltip}
                      />
                    );
                  })}
                </div>
              </div>
              
              <div className="flex gap-4 text-[9px] text-gray-500">
                <div className="flex items-center gap-1.5">
                  <div className="w-2.5 h-2.5 bg-blue-600/60 rounded-sm" />
                  <span>Frame Buffers (1.0MB)</span>
                </div>
                <div className="flex items-center gap-1.5">
                  <div className="w-2.5 h-2.5 bg-cyan-600/60 rounded-sm" />
                  <span>Depth Buffer (0.5MB)</span>
                </div>
                <div className="flex items-center gap-1.5">
                  <div className="w-2.5 h-2.5 bg-amber-600/60 rounded-sm" />
                  <span>Texture Memory (1.0MB)</span>
                </div>
                <div className="flex items-center gap-1.5">
                  <div className="w-2.5 h-2.5 bg-[#181d24] rounded-sm" />
                  <span>Unallocated (1.5MB)</span>
                </div>
              </div>
            </div>
          )}

          {activeTab === 'dvd' && (
            <div className="grid grid-cols-1 md:grid-cols-12 gap-4 h-full">
              {/* DVD Drive graphic dashboard */}
              <div className="md:col-span-5 bg-[#090c0f] border border-[#1e242c] rounded-lg p-3 flex flex-col items-center justify-between text-center space-y-3 relative overflow-hidden">
                <div className="absolute top-0 inset-x-0 h-0.5 bg-gradient-to-r from-transparent via-blue-500/30 to-transparent" />
                
                <div className="space-y-1">
                  <span className="text-[10px] text-gray-500 font-bold uppercase tracking-wider block font-mono">Physical Optical Drive</span>
                  <div className="flex items-center justify-center gap-2">
                    <span className={`w-2 h-2 rounded-full ${isRunning ? 'bg-emerald-500 animate-pulse' : 'bg-red-500'}`} />
                    <span className="text-gray-300 text-[9px] font-bold uppercase font-mono">{isRunning ? 'Disc Spun (4x CAV)' : 'Tray Closed / Idle'}</span>
                  </div>
                </div>

                {/* Spinning Disk */}
                <div className="relative my-2">
                  <div className={`w-24 h-24 rounded-full bg-gradient-to-r from-gray-800 via-slate-700 to-gray-800 border-2 border-gray-600 flex items-center justify-center shadow-lg relative ${isRunning && !isZoneLoading ? 'animate-spin' : ''} ${isZoneLoading ? 'animate-pulse duration-75' : ''}`}>
                    {/* Inner hole */}
                    <div className="w-8 h-8 rounded-full bg-[#0b0d10] border-4 border-gray-600 flex items-center justify-center">
                      <div className="w-3 h-3 rounded-full bg-gray-700" />
                    </div>
                    {/* Reflective shine lines */}
                    <div className="absolute inset-0 rounded-full bg-gradient-to-tr from-cyan-500/10 via-transparent to-pink-500/10 mix-blend-color-dodge pointer-events-none" />
                  </div>
                  {/* Laser head tracker */}
                  <div className="absolute bottom-1 right-2 bg-red-500/20 border border-red-500/50 rounded px-1.5 py-0.5 text-[8px] text-red-400 font-bold tracking-tighter flex items-center gap-1">
                    <span className="w-1 h-1 bg-red-500 rounded-full animate-ping" />
                    <span>LASER TRACKING</span>
                  </div>
                </div>

                <div className="w-full space-y-1.5 text-[8.5px] text-left border-t border-[#1e242c] pt-2 font-mono">
                  <div className="flex justify-between">
                    <span className="text-gray-500">Device Path:</span>
                    <span className="text-gray-300 font-semibold">cdrom0:\\\\</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-gray-500">Current Sector LBA:</span>
                    <span className="text-blue-400 font-mono font-bold">{isRunning ? activeDvdSector.toLocaleString() : '---'}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-gray-500">Read Transfer Rate:</span>
                    <span className="text-gray-400 font-semibold">{isRunning ? (isZoneLoading ? '5.28 MB/s (Burst)' : '1.35 MB/s (Streaming)') : '0.00 KB/s'}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-gray-500">IOP Disc Buffer:</span>
                    <span className="text-emerald-400 font-mono font-bold">{isRunning ? (isZoneLoading ? 'Streaming...' : '100% Buffered') : 'Empty'}</span>
                  </div>
                </div>
              </div>

              {/* Disc Directory & Active Script Buffer */}
              <div className="md:col-span-7 flex flex-col space-y-2 h-full min-h-0">
                <div className="bg-[#090c0f] border border-[#1e242c] rounded-lg p-2.5 flex-1 flex flex-col min-h-0">
                  <div className="border-b border-[#1e242c] pb-1.5 mb-2 flex justify-between items-center shrink-0">
                    <span className="text-[9px] text-gray-400 uppercase font-bold tracking-wider flex items-center gap-1.5 font-mono">
                      <Terminal className="w-3.5 h-3.5 text-blue-400" />
                      Dynamic DVD Script Buffer
                    </span>
                    <span className="text-[8.5px] bg-blue-500/10 border border-blue-500/20 text-blue-400 px-1.5 py-0.5 rounded font-mono font-bold uppercase">
                      Active: {GAME_CHAPTERS[currentChapterIdx].scriptFile}
                    </span>
                  </div>

                  {/* Active Command parser listing */}
                  <div className="flex-1 overflow-y-auto space-y-1 font-mono text-[9px] text-gray-500 p-1.5 bg-[#06080b] border border-[#14181d] rounded">
                    <div className="text-gray-500 italic pb-1"># Parsing commands in real-time off physical DVD tracks...</div>
                    
                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded bg-blue-950/20 border border-blue-900/30 text-blue-300">
                      <span className="text-[8px] font-bold text-blue-400 select-none">CMD 1:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">ZONE_INIT</span>
                        <span className="text-gray-400"> 0x0{activeZoneIdx + 1}</span>
                        <span className="text-blue-400/80 italic ml-2"># {GAME_CHAPTERS[currentChapterIdx].zones[activeZoneIdx]}</span>
                      </div>
                      <span className="text-[8px] bg-emerald-500/20 text-emerald-400 px-1 rounded uppercase font-bold tracking-tight">ACTIVE</span>
                    </div>

                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded hover:bg-[#0f131a]">
                      <span className="text-[8px] font-bold select-none">CMD 2:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">PURGE_MEM</span>
                        <span className="text-gray-500 italic ml-2"># Flush old level & monster textures to prevent 32MB overflow</span>
                      </div>
                      <span className="text-[8px] text-gray-500">EXECTD</span>
                    </div>

                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded hover:bg-[#0f131a]">
                      <span className="text-[8px] font-bold select-none">CMD 3:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">VRAM_LOAD</span>
                        <span className="text-amber-300"> "cdrom0:\\LEVELS\\CHAPTER_{currentChapterIdx+1}\\ZONE_{activeZoneIdx+1}.PNG;1"</span>
                        <span className="text-blue-400">, 0x00100000</span>
                      </div>
                      <span className="text-[8px] text-gray-500">EXECTD</span>
                    </div>

                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded hover:bg-[#0f131a]">
                      <span className="text-[8px] font-bold select-none">CMD 4:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">SPAWN_ENEMY</span>
                        <span className="text-amber-300"> "cdrom0:\\ASSETS\\MONSTERS.OBJ"</span>
                        <span className="text-blue-400">, 14.2, 0.0, -12.5</span>
                      </div>
                      <span className="text-[8px] text-gray-500">EXECTD</span>
                    </div>

                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded hover:bg-[#0f131a]">
                      <span className="text-[8px] font-bold select-none">CMD 5:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">SET_CAMERA_TARGET</span>
                        <span className="text-blue-400"> 14.2, 3.5, -12.0</span>
                      </div>
                      <span className="text-[8px] text-gray-500">EXECTD</span>
                    </div>

                    <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded hover:bg-[#0f131a] text-gray-300">
                      <span className="text-[8px] font-bold select-none">CMD 6:</span>
                      <div className="flex-1">
                        <span className="text-pink-400 font-bold">LOAD_DIALOGUE</span>
                        <span className="text-amber-300"> "{GAME_CHAPTERS[currentChapterIdx].speaker}"</span>
                        <span className="text-gray-400">, "{GAME_CHAPTERS[currentChapterIdx].line.substring(0, 24)}..."</span>
                      </div>
                      <span className="text-[8px] text-emerald-400 font-bold">LOADED</span>
                    </div>

                    {currentChapterIdx === 6 && (
                      <div className="flex items-start gap-2.5 py-0.5 px-1.5 rounded bg-red-950/20 border border-red-900/30 text-red-300 mt-1">
                        <span className="text-[8px] font-bold text-red-400 select-none">CMD 7:</span>
                        <div className="flex-1">
                          <span className="text-pink-400 font-bold">TRIGGER_GLITCH</span>
                          <span className="text-red-400 font-black"> "WITNESS MODE ACTIVE"</span>
                        </div>
                        <span className="text-[8px] bg-red-500/20 text-red-400 px-1 rounded uppercase font-bold tracking-tight animate-pulse">ARMED</span>
                      </div>
                    )}
                  </div>
                </div>
              </div>
            </div>
          )}

        </div>
      </div>
    </div>
  );
};
