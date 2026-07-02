/**
 * @file level_builder.cpp
 * @brief Implement Act I Spatial level layouts and coordinates stitching.
 */

#include "level_builder.hpp"

namespace TheSeventhVow {

LevelBuilder::LevelBuilder() {}
LevelBuilder::~LevelBuilder() {}

LevelLayout LevelBuilder::buildScene1_1_Courtyard() {
    LevelLayout layout;
    layout.sceneId = 11;
    layout.sceneTitle = "Scene 1.1: House Tyr Border Garrison Courtyard (Exterior)";

    // Enclose 100x100 boundary with modular granite wall meshes
    // Wall North
    LevelMeshNode wallN;
    wallN.name = "Garrison_Wall_North";
    wallN.position.set(0.0f, 0.0f, 50.0f, 1.0f);
    wallN.rotation.set(0.0f, 0.0f, 0.0f, 0.0f);
    wallN.scale.set(100.0f, 15.0f, 2.0f, 1.0f);
    wallN.assetPath = "ASSETS\\LEVELS\\TYR_WALL.OBJ;1";
    wallN.animAdapter.assignGenericTracks(1); // Static mesh
    layout.staticMeshes.push_back(wallN);

    // Wall South (locked iron gate centered at (0, 0, -50))
    LevelMeshNode wallS;
    wallS.name = "Garrison_Wall_South";
    wallS.position.set(0.0f, 0.0f, -50.0f, 1.0f);
    wallS.rotation.set(0.0f, 0.0f, 0.0f, 0.0f);
    wallS.scale.set(80.0f, 15.0f, 2.0f, 1.0f); // Leave 20 unit gap for gate
    wallS.assetPath = "ASSETS\\LEVELS\\TYR_WALL.OBJ;1";
    wallS.animAdapter.assignGenericTracks(1);
    layout.staticMeshes.push_back(wallS);

    LevelMeshNode gate;
    gate.name = "Locked_Iron_Gate";
    gate.position.set(0.0f, 0.0f, -50.0f, 1.0f);
    gate.rotation.set(0.0f, 0.0f, 0.0f, 0.0f);
    gate.scale.set(20.0f, 12.0f, 1.5f, 1.0f);
    gate.assetPath = "ASSETS\\PROPS\\IRON_GATE.OBJ;1";
    gate.animAdapter.assignGenericTracks(2); // Open / Closed states
    layout.props.push_back(gate);

    // Main Keep Entryway centered at (0, 0, 50)
    LevelMeshNode keepEntrance;
    keepEntrance.name = "White_Stone_Keep_Entryway";
    keepEntrance.position.set(0.0f, 0.0f, 48.0f, 1.0f);
    keepEntrance.rotation.set(0.0f, 180.0f, 0.0f, 0.0f);
    keepEntrance.scale.set(15.0f, 20.0f, 8.0f, 1.0f);
    keepEntrance.assetPath = "ASSETS\\LEVELS\\KEEP_ARCH.OBJ;1";
    keepEntrance.animAdapter.assignGenericTracks(1);
    layout.staticMeshes.push_back(keepEntrance);

    // Props: Barracks lean-to, weapon racks, braziers
    LevelMeshNode leanTo;
    leanTo.name = "Barracks_LeanTo";
    leanTo.position.set(-35.0f, 0.0f, -10.0f, 1.0f);
    leanTo.scale.set(12.0f, 8.0f, 12.0f, 1.0f);
    leanTo.assetPath = "ASSETS\\PROPS\\LEANTO.OBJ;1";
    layout.props.push_back(leanTo);

    LevelMeshNode weaponRack;
    weaponRack.name = "Weapon_Rack_Halberds";
    weaponRack.position.set(15.0f, 0.0f, -30.0f, 1.0f);
    weaponRack.scale.set(3.0f, 4.0f, 1.5f, 1.0f);
    weaponRack.assetPath = "ASSETS\\PROPS\\RACK.OBJ;1";
    layout.props.push_back(weaponRack);

    // Dynamic brazier lights
    LevelMeshNode brazier1;
    brazier1.name = "Brazier_Left";
    brazier1.position.set(-20.0f, 0.0f, 30.0f, 1.0f);
    brazier1.scale.set(2.0f, 3.5f, 2.0f, 1.0f);
    brazier1.assetPath = "ASSETS\\PROPS\\BRAZIER.OBJ;1";
    layout.props.push_back(brazier1);

    LevelMeshNode brazier2;
    brazier2.name = "Brazier_Right";
    brazier2.position.set(20.0f, 0.0f, 30.0f, 1.0f);
    brazier2.scale.set(2.0f, 3.5f, 2.0f, 1.0f);
    brazier2.assetPath = "ASSETS\\PROPS\\BRAZIER.OBJ;1";
    layout.props.push_back(brazier2);

    // Triggers: Keep entry loadzone
    LevelTrigger keepLoadTrigger;
    keepLoadTrigger.minBound.set(-8.0f, 0.0f, 45.0f, 1.0f);
    keepLoadTrigger.maxBound.set(8.0f, 10.0f, 52.0f, 1.0f);
    keepLoadTrigger.actionType = "LOAD_SCENE_1_2";
    keepLoadTrigger.isTriggered = false;
    layout.triggers.push_back(keepLoadTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene1_2_StrategyHall() {
    LevelLayout layout;
    layout.sceneId = 12;
    layout.sceneTitle = "Scene 1.2: The Grand Strategy Hall (Interior)";

    // Stone pillars spaced exactly 20 units apart along Z-axis (Z from 0 to 100)
    for (int z = 10; z <= 90; z += 20) {
        LevelMeshNode pillarLeft;
        pillarLeft.name = "Strategy_Pillar_L_" + std::to_string(z);
        pillarLeft.position.set(-15.0f, 0.0f, static_cast<float>(z), 1.0f);
        pillarLeft.scale.set(2.5f, 18.0f, 2.5f, 1.0f);
        pillarLeft.assetPath = "ASSETS\\LEVELS\\STONE_PILLAR.OBJ;1";
        layout.staticMeshes.push_back(pillarLeft);

        LevelMeshNode pillarRight;
        pillarRight.name = "Strategy_Pillar_R_" + std::to_string(z);
        pillarRight.position.set(15.0f, 0.0f, static_cast<float>(z), 1.0f);
        pillarRight.scale.set(2.5f, 18.0f, 2.5f, 1.0f);
        pillarRight.assetPath = "ASSETS\\LEVELS\\STONE_PILLAR.OBJ;1";
        layout.staticMeshes.push_back(pillarRight);
    }

    // Elevated stone dais platform
    LevelMeshNode platform;
    platform.name = "Elevated_Strategy_Dais";
    platform.position.set(0.0f, 1.5f, 115.0f, 1.0f);
    platform.scale.set(20.0f, 3.0f, 15.0f, 1.0f);
    platform.assetPath = "ASSETS\\LEVELS\\DAIS.OBJ;1";
    layout.staticMeshes.push_back(platform);

    // War table centered at (0, 5, 120) - table is on top of dais
    LevelMeshNode warTable;
    warTable.name = "Strategic_War_Table";
    warTable.position.set(0.0f, 5.0f, 120.0f, 1.0f);
    warTable.scale.set(6.0f, 3.0f, 4.0f, 1.0f);
    warTable.assetPath = "ASSETS\\PROPS\\WAR_TABLE.OBJ;1";
    layout.props.push_back(warTable);

    // Collision trigger behind dais (Z = 125) to fade to next scene
    LevelTrigger balconyTrigger;
    balconyTrigger.minBound.set(-10.0f, 0.0f, 122.0f, 1.0f);
    balconyTrigger.maxBound.set(10.0f, 10.0f, 130.0f, 1.0f);
    balconyTrigger.actionType = "LOAD_SCENE_1_3_BALCONY";
    balconyTrigger.isTriggered = false;
    layout.triggers.push_back(balconyTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene1_3_Battlements() {
    LevelLayout layout;
    layout.sceneId = 13;
    layout.sceneTitle = "Scene 1.3: The Burning Battlements (Exterior)";

    // Linear stone walkway along Z-axis (Z from 0 to 120)
    for (int z = 0; z <= 100; z += 20) {
        LevelMeshNode walkSegment;
        walkSegment.name = "Battlement_Walkway_Seg_" + std::to_string(z);
        walkSegment.position.set(0.0f, 10.0f, static_cast<float>(z), 1.0f);
        walkSegment.scale.set(10.0f, 2.0f, 20.0f, 1.0f);
        walkSegment.assetPath = "ASSETS\\LEVELS\\WALKWAY_SEG.OBJ;1";
        layout.staticMeshes.push_back(walkSegment);

        // Crenellated protective left parapet overlooking burning canyon
        LevelMeshNode parapet;
        parapet.name = "Battlement_Parapet_L_" + std::to_string(z);
        parapet.position.set(-5.0f, 12.0f, static_cast<float>(z), 1.0f);
        parapet.scale.set(0.5f, 4.0f, 20.0f, 1.0f);
        parapet.assetPath = "ASSETS\\LEVELS\\PARAPET.OBJ;1";
        layout.staticMeshes.push_back(parapet);
    }

    // Wooden scaffolding ramp mesh at the end leading up to flat tower platform at height Y = 30
    LevelMeshNode scaffolding;
    scaffolding.name = "Wooden_Scaffolding_Ramp";
    scaffolding.position.set(0.0f, 20.0f, 110.0f, 1.0f);
    scaffolding.scale.set(8.0f, 10.0f, 15.0f, 1.0f);
    scaffolding.assetPath = "ASSETS\\LEVELS\\SCAFFOLD_RAMP.OBJ;1";
    layout.staticMeshes.push_back(scaffolding);

    // Guard tower platform height Y = 30
    LevelMeshNode towerPlatform;
    towerPlatform.name = "High_Guard_Tower_Platform";
    towerPlatform.position.set(0.0f, 30.0f, 130.0f, 1.0f);
    towerPlatform.scale.set(20.0f, 2.0f, 20.0f, 1.0f);
    towerPlatform.assetPath = "ASSETS\\LEVELS\\TOWER_PLATFORM.OBJ;1";
    layout.staticMeshes.push_back(towerPlatform);

    // Props: Burning crates & broken arrow carts
    LevelMeshNode burningCrate;
    burningCrate.name = "Burning_Supply_Crate";
    burningCrate.position.set(-3.0f, 11.5f, 45.0f, 1.0f);
    burningCrate.scale.set(2.0f, 2.0f, 2.0f, 1.0f);
    burningCrate.assetPath = "ASSETS\\PROPS\\CRATE_FIRE.OBJ;1";
    layout.props.push_back(burningCrate);

    LevelMeshNode brokenCart;
    brokenCart.name = "Broken_Arrow_Cart";
    brokenCart.position.set(3.0f, 11.0f, 75.0f, 1.0f);
    brokenCart.scale.set(4.0f, 3.0f, 5.0f, 1.0f);
    brokenCart.assetPath = "ASSETS\\PROPS\\CART_DESTRUCT.OBJ;1";
    layout.props.push_back(brokenCart);

    // Enemy spawns (Masked Marauders along the walkway)
    LevelMeshNode marauderSpawn1;
    marauderSpawn1.name = "Marauder_Grunt_1";
    marauderSpawn1.position.set(-2.0f, 11.0f, 30.0f, 1.0f);
    marauderSpawn1.assetPath = "ASSETS\\ENEMIES\\MARAUDER.OBJ;1";
    marauderSpawn1.animAdapter.assignGenericTracks(4); // Idle, Walk, Slash, Die
    layout.enemySpawns.push_back(marauderSpawn1);

    LevelMeshNode marauderSpawn2;
    marauderSpawn2.name = "Marauder_Grunt_2";
    marauderSpawn2.position.set(2.0f, 11.0f, 60.0f, 1.0f);
    marauderSpawn2.assetPath = "ASSETS\\ENEMIES\\MARAUDER.OBJ;1";
    marauderSpawn2.animAdapter.assignGenericTracks(4);
    layout.enemySpawns.push_back(marauderSpawn2);

    // Imigh (Boss) spawning on high tower platform
    LevelMeshNode imighBoss;
    imighBoss.name = "Timeless_Acolyte_Imigh_Boss";
    imighBoss.position.set(0.0f, 31.0f, 135.0f, 1.0f);
    imighBoss.assetPath = "ASSETS\\ENEMIES\\IMIGH.OBJ;1";
    imighBoss.animAdapter.assignGenericTracks(5); // Idle, Walk, Spellcast, Hurt, Rise
    layout.enemySpawns.push_back(imighBoss);

    return layout;
}

LevelLayout LevelBuilder::buildScene2_1_RainyBasalt() {
    LevelLayout layout;
    layout.sceneId = 21;
    layout.sceneTitle = "Scene 2.1: The Rainy Basalt Perimeter (Exterior)";

    // Winding basalt gorge walls
    for (int z = 10; z <= 240; z += 30) {
        LevelMeshNode basaltL;
        basaltL.name = "Basalt_Rock_Left_" + std::to_string(z);
        basaltL.position.set(-12.0f, static_cast<float>(z) * 0.06f, static_cast<float>(z), 1.0f); // ascending path
        basaltL.scale.set(10.0f, 35.0f, 15.0f, 1.0f);
        basaltL.assetPath = "ASSETS\\LEVELS\\BASALT_WALL.OBJ;1";
        layout.staticMeshes.push_back(basaltL);

        LevelMeshNode basaltR;
        basaltR.name = "Basalt_Rock_Right_" + std::to_string(z);
        basaltR.position.set(12.0f, static_cast<float>(z) * 0.06f, static_cast<float>(z), 1.0f);
        basaltR.scale.set(10.0f, 35.0f, 15.0f, 1.0f);
        basaltR.assetPath = "ASSETS\\LEVELS\\BASALT_WALL.OBJ;1";
        layout.staticMeshes.push_back(basaltR);

        // Security fence lines
        LevelMeshNode fence;
        fence.name = "Iron_Security_Fence_" + std::to_string(z);
        fence.position.set(-8.0f, (static_cast<float>(z) * 0.06f) + 2.0f, static_cast<float>(z), 1.0f);
        fence.scale.set(1.0f, 4.0f, 10.0f, 1.0f);
        fence.assetPath = "ASSETS\\PROPS\\IRON_FENCE.OBJ;1";
        layout.props.push_back(fence);
    }

    // Overturned transport carts
    LevelMeshNode cart;
    cart.name = "Overturned_Transport_Cart";
    cart.position.set(-4.0f, 3.0f, 50.0f, 1.0f);
    cart.scale.set(3.0f, 3.0f, 4.0f, 1.0f);
    cart.assetPath = "ASSETS\\PROPS\\TRANS_CART.OBJ;1";
    layout.props.push_back(cart);

    // Rusty chains details
    LevelMeshNode chains;
    chains.name = "Rusty_Hanging_Chains";
    chains.position.set(0.0f, 10.0f, 120.0f, 1.0f);
    chains.scale.set(1.0f, 8.0f, 1.0f, 1.0f);
    chains.assetPath = "ASSETS\\PROPS\\RUSTY_CHAINS.OBJ;1";
    layout.props.push_back(chains);

    // Rain global particle emitter marker (non-renderable node)
    LevelMeshNode rainEmitter;
    rainEmitter.name = "Global_Rain_Particle_Emitter";
    rainEmitter.position.set(0.0f, 40.0f, 120.0f, 1.0f);
    rainEmitter.assetPath = "SYSTEM\\EMITTERS\\RAIN.INI;1";
    layout.props.push_back(rainEmitter);

    // Mechanical iron lift platform at (0, 15, 250) (docking up to Y=80)
    LevelMeshNode mechanicalLift;
    mechanicalLift.name = "Mechanical_Iron_Lift";
    mechanicalLift.position.set(0.0f, 15.0f, 250.0f, 1.0f);
    mechanicalLift.scale.set(15.0f, 1.5f, 15.0f, 1.0f);
    mechanicalLift.assetPath = "ASSETS\\LEVELS\\IRON_LIFT.OBJ;1";
    mechanicalLift.animAdapter.assignGenericTracks(3); // Ascend, Descend, Static
    layout.props.push_back(mechanicalLift);

    // Starved Echo entity spawns along the ascending canyon
    LevelMeshNode echo1;
    echo1.name = "Starved_Echo_Grunt_1";
    echo1.position.set(-3.0f, 5.0f, 80.0f, 1.0f);
    echo1.assetPath = "ASSETS\\ENEMIES\\ECHO_STARVED.OBJ;1";
    echo1.animAdapter.assignGenericTracks(4); // Idle, Walk, Claw, Die
    layout.enemySpawns.push_back(echo1);

    LevelMeshNode echo2;
    echo2.name = "Starved_Echo_Grunt_2";
    echo2.position.set(3.0f, 10.0f, 160.0f, 1.0f);
    echo2.assetPath = "ASSETS\\ENEMIES\\ECHO_STARVED.OBJ;1";
    echo2.animAdapter.assignGenericTracks(4);
    layout.enemySpawns.push_back(echo2);

    // Lift trigger to ascend from Y=15 to Y=80
    LevelTrigger liftTrigger;
    liftTrigger.minBound.set(-7.0f, 14.0f, 243.0f, 1.0f);
    liftTrigger.maxBound.set(7.0f, 20.0f, 257.0f, 1.0f);
    liftTrigger.actionType = "ACTIVATE_LIFT_Y80";
    liftTrigger.isTriggered = false;
    layout.triggers.push_back(liftTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene2_2_ObsidianPanopticon() {
    LevelLayout layout;
    layout.sceneId = 22;
    layout.sceneTitle = "Scene 2.2: The Obsidian Panopticon (Interior)";

    // Hollow circular layout - perimeter ring walkway centered at (0, 0, 0)
    // Walkway segments placed around a circle of radius 50. Let's place 8 segments (45 deg apart)
    for (int i = 0; i < 8; ++i) {
        float angle = static_cast<float>(i) * 45.0f * (3.14159f / 180.0f);
        float x = cos(angle) * 50.0f;
        float z = sin(angle) * 50.0f;

        LevelMeshNode walkSeg;
        walkSeg.name = "Panopticon_Ring_Walkway_Seg_" + std::to_string(i);
        walkSeg.position.set(x, 15.0f, z, 1.0f);
        walkSeg.rotation.set(0.0f, -static_cast<float>(i) * 45.0f, 0.0f, 1.0f);
        walkSeg.scale.set(12.0f, 1.5f, 20.0f, 1.0f);
        walkSeg.assetPath = "ASSETS\\LEVELS\\PAN_WALKWAY.OBJ;1";
        layout.staticMeshes.push_back(walkSeg);

        // Hanging cells suspended from ceiling
        LevelMeshNode hangingCell;
        hangingCell.name = "Hanging_Prison_Cage_" + std::to_string(i);
        hangingCell.position.set(x * 0.7f, 35.0f, z * 0.7f, 1.0f); // Hanging closer to center pit
        hangingCell.scale.set(3.0f, 5.0f, 3.0f, 1.0f);
        hangingCell.assetPath = "ASSETS\\PROPS\\HANGING_CAGE.OBJ;1";
        layout.props.push_back(hangingCell);
    }

    // Exposed iron gears details near center
    LevelMeshNode gears;
    gears.name = "Exposed_Panopticon_Iron_Gears";
    gears.position.set(0.0f, -2.0f, 0.0f, 1.0f);
    gears.scale.set(15.0f, 3.0f, 15.0f, 1.0f);
    gears.assetPath = "ASSETS\\LEVELS\\PAN_GEARS.OBJ;1";
    layout.staticMeshes.push_back(gears);

    // High pressure steam pipes & valve coordinates to clear path
    LevelMeshNode valve1;
    valve1.name = "Steam_Control_Valve_1";
    valve1.position.set(50.0f, 16.5f, 0.0f, 1.0f); // 0 degrees
    valve1.scale.set(1.5f, 1.5f, 1.5f, 1.0f);
    valve1.assetPath = "ASSETS\\PROPS\\STEAM_VALVE.OBJ;1";
    layout.props.push_back(valve1);

    LevelMeshNode valve2;
    valve2.name = "Steam_Control_Valve_2";
    valve2.position.set(-35.3f, 16.5f, 35.3f, 1.0f); // 135 degrees
    valve2.scale.set(1.5f, 1.5f, 1.5f, 1.0f);
    valve2.assetPath = "ASSETS\\PROPS\\STEAM_VALVE.OBJ;1";
    layout.props.push_back(valve2);

    LevelMeshNode valve3;
    valve3.name = "Steam_Control_Valve_3";
    valve3.position.set(-35.3f, 16.5f, -35.3f, 1.0f); // 225 degrees
    valve3.scale.set(1.5f, 1.5f, 1.5f, 1.0f);
    valve3.assetPath = "ASSETS\\PROPS\\STEAM_VALVE.OBJ;1";
    layout.props.push_back(valve3);

    // Glowing red security lamps
    for (int i = 1; i <= 3; ++i) {
        LevelMeshNode redLamp;
        redLamp.name = "Red_Security_Lamp_" + std::to_string(i);
        redLamp.position.set(cos(static_cast<float>(i) * 120.0f * (3.14159f / 180.0f)) * 48.0f, 22.0f,
                             sin(static_cast<float>(i) * 120.0f * (3.14159f / 180.0f)) * 48.0f, 1.0f);
        redLamp.scale.set(1.0f, 1.5f, 1.0f, 1.0f);
        redLamp.assetPath = "ASSETS\\PROPS\\RED_LAMP.OBJ;1";
        layout.props.push_back(redLamp);
    }

    // Lower holding cells structure
    LevelMeshNode cells;
    cells.name = "Lower_Holding_Cells_Sectors";
    cells.position.set(0.0f, 5.0f, -45.0f, 1.0f);
    cells.scale.set(15.0f, 8.0f, 10.0f, 1.0f);
    cells.assetPath = "ASSETS\\LEVELS\\PRISON_CELLS.OBJ;1";
    layout.staticMeshes.push_back(cells);

    // Three Steam wall collision blocks to deactivate
    LevelTrigger steamWall1;
    steamWall1.minBound.set(45.0f, 15.0f, -5.0f, 1.0f);
    steamWall1.maxBound.set(55.0f, 25.0f, 5.0f, 1.0f);
    steamWall1.actionType = "STEAM_WALL_SECTOR_1";
    steamWall1.isTriggered = false;
    layout.triggers.push_back(steamWall1);

    // Choice prompt zone (refugees rescue)
    LevelTrigger refugeeChoiceTrigger;
    refugeeChoiceTrigger.minBound.set(-10.0f, 5.0f, -50.0f, 1.0f);
    refugeeChoiceTrigger.maxBound.set(10.0f, 12.0f, -38.0f, 1.0f);
    refugeeChoiceTrigger.actionType = "TRIGGER_REFUGEE_CHOICE_PROMPT";
    refugeeChoiceTrigger.isTriggered = false;
    layout.triggers.push_back(refugeeChoiceTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene2_3_ExecutionScaffold() {
    LevelLayout layout;
    layout.sceneId = 23;
    layout.sceneTitle = "Scene 2.3: The Execution Scaffold (Exterior/Interior Hybrid)";

    // Flat roof deck platform mesh
    LevelMeshNode roofDeck;
    roofDeck.name = "Execution_Roof_Deck_Platform";
    roofDeck.position.set(0.0f, 0.0f, 50.0f, 1.0f);
    roofDeck.scale.set(80.0f, 3.0f, 120.0f, 1.0f);
    roofDeck.assetPath = "ASSETS\\LEVELS\\EXECUTION_DECK.OBJ;1";
    layout.staticMeshes.push_back(roofDeck);

    // Flanking Gothic Spires
    LevelMeshNode spireL;
    spireL.name = "Gothic_Spire_Left";
    spireL.position.set(-30.0f, 15.0f, 80.0f, 1.0f);
    spireL.scale.set(8.0f, 40.0f, 8.0f, 1.0f);
    spireL.assetPath = "ASSETS\\LEVELS\\GOTHIC_SPIRE.OBJ;1";
    layout.staticMeshes.push_back(spireL);

    LevelMeshNode spireR;
    spireR.name = "Gothic_Spire_Right";
    spireR.position.set(30.0f, 15.0f, 80.0f, 1.0f);
    spireR.scale.set(8.0f, 40.0f, 8.0f, 1.0f);
    spireR.assetPath = "ASSETS\\LEVELS\\GOTHIC_SPIRE.OBJ;1";
    layout.staticMeshes.push_back(spireR);

    // Massive stone guillotine platform at center (0, 5, 100)
    LevelMeshNode guillotine;
    guillotine.name = "Central_Stone_Guillotine_Platform";
    guillotine.position.set(0.0f, 5.0f, 100.0f, 1.0f);
    guillotine.scale.set(12.0f, 10.0f, 12.0f, 1.0f);
    guillotine.assetPath = "ASSETS\\PROPS\\GUILLOTINE.OBJ;1";
    guillotine.animAdapter.assignGenericTracks(2); // Idle, Release Blade
    layout.props.push_back(guillotine);

    // Detail props: Executioner blocks, executioner halberds, braziers in the wind
    LevelMeshNode execBlock;
    execBlock.name = "Executioners_Chop_Block";
    execBlock.position.set(-5.0f, 5.0f, 92.0f, 1.0f);
    execBlock.scale.set(2.0f, 2.0f, 2.0f, 1.0f);
    execBlock.assetPath = "ASSETS\\PROPS\\EXEC_BLOCK.OBJ;1";
    layout.props.push_back(execBlock);

    LevelMeshNode halberdRack;
    halberdRack.name = "Executioners_Halberds_Display";
    halberdRack.position.set(15.0f, 1.5f, 70.0f, 1.0f);
    halberdRack.scale.set(3.0f, 5.0f, 1.5f, 1.0f);
    halberdRack.assetPath = "ASSETS\\PROPS\\EXEC_RACK.OBJ;1";
    layout.props.push_back(halberdRack);

    LevelMeshNode windyBrazier;
    windyBrazier.name = "Storm_Brazier_Active";
    windyBrazier.position.set(-20.0f, 1.5f, 50.0f, 1.0f);
    windyBrazier.scale.set(2.5f, 4.0f, 2.5f, 1.0f);
    windyBrazier.assetPath = "ASSETS\\PROPS\\WINDY_BRAZIER.OBJ;1";
    layout.props.push_back(windyBrazier);

    // Valen Inquisitor Boss Spawn Node
    LevelMeshNode inquisitorBoss;
    inquisitorBoss.name = "Valen_Inquisitor_Boss";
    inquisitorBoss.position.set(0.0f, 5.5f, 103.0f, 1.0f);
    inquisitorBoss.scale.set(1.2f, 1.2f, 1.2f, 1.0f);
    inquisitorBoss.assetPath = "ASSETS\\ENEMIES\\INQUISITOR.OBJ;1";
    inquisitorBoss.animAdapter.assignGenericTracks(5); // Idle, Walk, HeavySlash, CastPunish, Die
    layout.enemySpawns.push_back(inquisitorBoss);

    // Heavy iron portcullis mesh at (0, 5, 40) that drops cutting path
    LevelMeshNode portcullis;
    portcullis.name = "Slam_Portcullis_Gate";
    portcullis.position.set(0.0f, 5.0f, 40.0f, 1.0f);
    portcullis.scale.set(15.0f, 12.0f, 1.5f, 1.0f);
    portcullis.assetPath = "ASSETS\\PROPS\\PORTCULLIS.OBJ;1";
    portcullis.animAdapter.assignGenericTracks(2); // Up, SlamDown
    layout.props.push_back(portcullis);

    // Church reinforcements trigger and portcullis drop trigger
    LevelTrigger postBossTrigger;
    postBossTrigger.minBound.set(-15.0f, 0.0f, 85.0f, 1.0f);
    postBossTrigger.maxBound.set(15.0f, 10.0f, 115.0f, 1.0f);
    postBossTrigger.actionType = "TRIGGER_BOSS_DEATH_PORTCULLIS_SLAM_Y40";
    postBossTrigger.isTriggered = false;
    layout.triggers.push_back(postBossTrigger);

    // Scaffold River leap trigger
    LevelTrigger riverLeap;
    riverLeap.minBound.set(-30.0f, 0.0f, 110.0f, 1.0f);
    riverLeap.maxBound.set(30.0f, 5.0f, 120.0f, 1.0f);
    riverLeap.actionType = "LEAP_INTO_VALEN_RIVER_ESCAPE";
    riverLeap.isTriggered = false;
    layout.triggers.push_back(riverLeap);

    return layout;
}

LevelLayout LevelBuilder::buildScene3_1_LimestonePromenade() {
    LevelLayout layout;
    layout.sceneId = 31;
    layout.sceneTitle = "Scene 3.1: The Immaculate Limestone Promenade (Exterior)";

    // Promenade street grid & archways
    for (int z = 0; z <= 330; z += 30) {
        LevelMeshNode streetTile;
        streetTile.name = "Marble_Street_Tile_" + std::to_string(z);
        streetTile.position.set(0.0f, static_cast<float>(z) * 0.057f, static_cast<float>(z), 1.0f); // gentle grade up
        streetTile.scale.set(16.0f, 1.0f, 30.0f, 1.0f);
        streetTile.assetPath = "ASSETS\\LEVELS\\MARBLE_TILE.OBJ;1";
        layout.staticMeshes.push_back(streetTile);

        // Romanesque white limestone arches flanking
        LevelMeshNode archL;
        archL.name = "Limestone_Arch_Left_" + std::to_string(z);
        archL.position.set(-10.0f, static_cast<float>(z) * 0.057f, static_cast<float>(z), 1.0f);
        archL.scale.set(2.0f, 14.0f, 6.0f, 1.0f);
        archL.assetPath = "ASSETS\\LEVELS\\SERIS_ARCH.OBJ;1";
        layout.staticMeshes.push_back(archL);

        // Gold lampposts
        LevelMeshNode lamp;
        lamp.name = "Gold_Lamppost_" + std::to_string(z);
        lamp.position.set(8.5f, (static_cast<float>(z) * 0.057f) + 1.0f, static_cast<float>(z), 1.0f);
        lamp.scale.set(1.0f, 6.0f, 1.0f, 1.0f);
        lamp.assetPath = "ASSETS\\PROPS\\GOLD_LAMP.OBJ;1";
        layout.props.push_back(lamp);
    }

    // Pristine marble water fountains
    LevelMeshNode fountain;
    fountain.name = "Pristine_Marble_Fountain";
    fountain.position.set(0.0f, 3.0f, 100.0f, 1.0f);
    fountain.scale.set(8.0f, 4.0f, 8.0f, 1.0f);
    fountain.assetPath = "ASSETS\\PROPS\\MARBLE_FOUNTAIN.OBJ;1";
    layout.props.push_back(fountain);

    // Decorative white drapery hanging
    LevelMeshNode drapes;
    drapes.name = "Hanging_Saint_White_Drape";
    drapes.position.set(-8.0f, 12.0f, 180.0f, 1.0f);
    drapes.scale.set(0.2f, 8.0f, 4.0f, 1.0f);
    drapes.assetPath = "ASSETS\\PROPS\\WHITE_DRAPE.OBJ;1";
    layout.props.push_back(drapes);

    // Cathedral complex entrance at (0, 20, 350)
    LevelMeshNode cathedralFacade;
    cathedralFacade.name = "Grand_Asylum_Cathedral_Facade";
    cathedralFacade.position.set(0.0f, 20.0f, 350.0f, 1.0f);
    cathedralFacade.scale.set(25.0f, 35.0f, 12.0f, 1.0f);
    cathedralFacade.assetPath = "ASSETS\\LEVELS\\CATHEDRAL_FRONT.OBJ;1";
    layout.staticMeshes.push_back(cathedralFacade);

    // Flame Rank Knights Patrolling Routes (AI avoids detection)
    LevelMeshNode flameKnight1;
    flameKnight1.name = "Flame_Rank_Paladin_Patrol_1";
    flameKnight1.position.set(-4.0f, 6.0f, 120.0f, 1.0f);
    flameKnight1.assetPath = "ASSETS\\ENEMIES\\FLAME_KNIGHT.OBJ;1";
    flameKnight1.animAdapter.assignGenericTracks(3); // Idle, Walk, SpearSweep
    layout.enemySpawns.push_back(flameKnight1);

    LevelMeshNode flameKnight2;
    flameKnight2.name = "Flame_Rank_Paladin_Patrol_2";
    flameKnight2.position.set(4.0f, 12.0f, 220.0f, 1.0f);
    flameKnight2.assetPath = "ASSETS\\ENEMIES\\FLAME_KNIGHT.OBJ;1";
    flameKnight2.animAdapter.assignGenericTracks(3);
    layout.enemySpawns.push_back(flameKnight2);

    // Broken stained-glass window infiltration route trigger (Z=348, side-route)
    LevelTrigger stainedGlassTrigger;
    stainedGlassTrigger.minBound.set(-14.0f, 18.0f, 345.0f, 1.0f);
    stainedGlassTrigger.maxBound.set(-10.0f, 24.0f, 352.0f, 1.0f);
    stainedGlassTrigger.actionType = "INFILTRATE_ASYLUM_STAINED_GLASS";
    stainedGlassTrigger.isTriggered = false;
    layout.triggers.push_back(stainedGlassTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene3_2_SanctumSanctuary() {
    LevelLayout layout;
    layout.sceneId = 32;
    layout.sceneTitle = "Scene 3.2: The Seris Sanctum Sanctuary (Interior)";

    // Cathedral columns line Z-axis
    for (int z = 15; z <= 105; z += 30) {
        LevelMeshNode colL;
        colL.name = "Sanctuary_Column_L_" + std::to_string(z);
        colL.position.set(-12.0f, 0.0f, static_cast<float>(z), 1.0f);
        colL.scale.set(3.0f, 24.0f, 3.0f, 1.0f);
        colL.assetPath = "ASSETS\\LEVELS\\WHITE_COLUMN.OBJ;1";
        layout.staticMeshes.push_back(colL);

        LevelMeshNode colR;
        colR.name = "Sanctuary_Column_R_" + std::to_string(z);
        colR.position.set(12.0f, 0.0f, static_cast<float>(z), 1.0f);
        colR.scale.set(3.0f, 24.0f, 3.0f, 1.0f);
        colR.assetPath = "ASSETS\\LEVELS\\WHITE_COLUMN.OBJ;1";
        layout.staticMeshes.push_back(colR);

        // Polished cherry-wood pews
        LevelMeshNode pewL;
        pewL.name = "Cherrywood_Pew_L_" + std::to_string(z);
        pewL.position.set(-6.0f, 0.0f, static_cast<float>(z) + 5.0f, 1.0f);
        pewL.scale.set(4.5f, 2.5f, 1.5f, 1.0f);
        pewL.assetPath = "ASSETS\\PROPS\\CHURCH_PEW.OBJ;1";
        layout.props.push_back(pewL);

        LevelMeshNode pewR;
        pewR.name = "Cherrywood_Pew_R_" + std::to_string(z);
        pewR.position.set(6.0f, 0.0f, static_cast<float>(z) + 5.0f, 1.0f);
        pewR.scale.set(4.5f, 2.5f, 1.5f, 1.0f);
        pewR.assetPath = "ASSETS\\PROPS\\CHURCH_PEW.OBJ;1";
        layout.props.push_back(pewR);
    }

    // Oversized white-and-gold altar centered at (0, 2, 120)
    LevelMeshNode altar;
    altar.name = "Sacred_WhiteGold_Altar";
    altar.position.set(0.0f, 2.0f, 120.0f, 1.0f);
    altar.scale.set(8.0f, 3.0f, 5.0f, 1.0f);
    altar.assetPath = "ASSETS\\PROPS\\SERIS_ALTAR.OBJ;1";
    altar.animAdapter.assignGenericTracks(2); // Slide Closed, Slide Open
    layout.props.push_back(altar);

    // Massive marble statue of the First Saint behind the altar (5, 2, 130)
    LevelMeshNode firstSaintStatue;
    firstSaintStatue.name = "First_Saint_Marble_Statue";
    firstSaintStatue.position.set(5.0f, 2.0f, 130.0f, 1.0f);
    firstSaintStatue.scale.set(4.0f, 12.0f, 4.0f, 1.0f);
    firstSaintStatue.assetPath = "ASSETS\\PROPS\\SAINT_STATUE.OBJ;1";
    layout.props.push_back(firstSaintStatue);

    // Golden incense censers
    LevelMeshNode censer1;
    censer1.name = "Golden_Incense_Censer_L";
    censer1.position.set(-6.0f, 4.0f, 115.0f, 1.0f);
    censer1.scale.set(1.5f, 3.0f, 1.5f, 1.0f);
    censer1.assetPath = "ASSETS\\PROPS\\GOLDEN_CENSER.OBJ;1";
    layout.props.push_back(censer1);

    // Holy Bible on podium prop
    LevelMeshNode biblePodium;
    biblePodium.name = "Sacrament_Holy_Bible_Podium";
    biblePodium.position.set(-3.0f, 1.5f, 110.0f, 1.0f);
    biblePodium.scale.set(1.5f, 4.0f, 1.5f, 1.0f);
    biblePodium.assetPath = "ASSETS\\PROPS\\BIBLE_PODIUM.OBJ;1";
    layout.props.push_back(biblePodium);

    // Interaction trigger behind statue at (5, 2, 130) for sliding altar sideways
    LevelTrigger secretCrestTrigger;
    secretCrestTrigger.minBound.set(3.0f, 1.0f, 127.0f, 1.0f);
    secretCrestTrigger.maxBound.set(7.0f, 5.0f, 133.0f, 1.0f);
    secretCrestTrigger.actionType = "TRIGGER_ALTAR_SLIDE_STAIRS_REVEAL";
    secretCrestTrigger.isTriggered = false;
    layout.triggers.push_back(secretCrestTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene3_3_UnderLab() {
    LevelLayout layout;
    layout.sceneId = 33;
    layout.sceneTitle = "Scene 3.3: The Soul-Harvesting Under-Lab (Interior Deep)";

    // Damp brick-and-iron dungeon grid walls
    for (int x = -20; x <= 20; x += 20) {
        for (int z = 10; z <= 130; z += 30) {
            LevelMeshNode pipeSeg;
            pipeSeg.name = "Exposed_Underlab_Copper_Pipe_" + std::to_string(x) + "_" + std::to_string(z);
            pipeSeg.position.set(static_cast<float>(x), 10.0f, static_cast<float>(z), 1.0f);
            pipeSeg.scale.set(1.0f, 1.0f, 10.0f, 1.0f);
            pipeSeg.assetPath = "ASSETS\\LEVELS\\COPPER_PIPES.OBJ;1";
            layout.staticMeshes.push_back(pipeSeg);
        }
    }

    // Giant glass alchemical vats with green light/glow settings (low-poly human silhouettes)
    for (int i = 1; i <= 4; ++i) {
        LevelMeshNode alchemVat;
        alchemVat.name = "Alchemical_Soul_Vat_" + std::to_string(i);
        alchemVat.position.set((i % 2 == 0) ? -12.0f : 12.0f, 0.0f, 30.0f * static_cast<float>(i), 1.0f);
        alchemVat.scale.set(4.0f, 10.0f, 4.0f, 1.0f);
        // Custom attribute marker for green under-glow effect
        alchemVat.assetPath = "ASSETS\\PROPS\\ALCHEM_VAT_GLOW_GREEN.OBJ;1";
        alchemVat.animAdapter.assignGenericTracks(2); // Inactive, FluidBubbles
        layout.props.push_back(alchemVat);
    }

    // Blood-stained metal operating tables
    LevelMeshNode opTable1;
    opTable1.name = "Blood_Stained_Operating_Table_A";
    opTable1.position.set(-5.0f, 1.5f, 50.0f, 1.0f);
    opTable1.scale.set(3.0f, 2.5f, 6.0f, 1.0f);
    opTable1.assetPath = "ASSETS\\PROPS\\OP_TABLE_BLOODY.OBJ;1";
    layout.props.push_back(opTable1);

    // Leather restraint chair
    LevelMeshNode restraintChair;
    restraintChair.name = "Leather_Subject_Restraint_Chair";
    restraintChair.position.set(5.0f, 1.0f, 80.0f, 1.0f);
    restraintChair.scale.set(2.5f, 3.5f, 2.5f, 1.0f);
    restraintChair.assetPath = "ASSETS\\PROPS\\RESTRAINT_CHAIR.OBJ;1";
    layout.props.push_back(restraintChair);

    // Mutated early Echo prototype enemies
    LevelMeshNode mutant1;
    mutant1.name = "Early_Echo_Mutant_Prototype_1";
    mutant1.position.set(-6.0f, 1.0f, 40.0f, 1.0f);
    mutant1.assetPath = "ASSETS\\ENEMIES\\ECHO_MUTATED.OBJ;1";
    mutant1.animAdapter.assignGenericTracks(4); // Idle, Walk, MutatedStrike, Collapse
    layout.enemySpawns.push_back(mutant1);

    LevelMeshNode mutant2;
    mutant2.name = "Early_Echo_Mutant_Prototype_2";
    mutant2.position.set(6.0f, 1.0f, 90.0f, 1.0f);
    mutant2.assetPath = "ASSETS\\ENEMIES\\ECHO_MUTATED.OBJ;1";
    mutant2.animAdapter.assignGenericTracks(4);
    layout.enemySpawns.push_back(mutant2);

    // Central operating theater boss room: Archbishop Seris
    LevelMeshNode archbishopSeris;
    archbishopSeris.name = "Archbishop_Seris_Mutating_Acolyte_Boss";
    archbishopSeris.position.set(0.0f, 2.0f, 120.0f, 1.0f);
    archbishopSeris.scale.set(1.4f, 1.4f, 1.4f, 1.0f);
    archbishopSeris.assetPath = "ASSETS\\ENEMIES\\SERIS_BOSS.OBJ;1";
    archbishopSeris.animAdapter.assignGenericTracks(5); // HumanPreach, DrinkEssence, AbominableForm, SlamStrike, Obliterate
    layout.enemySpawns.push_back(archbishopSeris);

    // Imigh watching boss fight from top of fluid vats at (12, 10, 120)
    LevelMeshNode imighSpectator;
    imighSpectator.name = "Imigh_Careless_Spectator_EasterEgg";
    imighSpectator.position.set(12.0f, 10.0f, 120.0f, 1.0f);
    imighSpectator.scale.set(1.0f, 1.0f, 1.0f, 1.0f);
    imighSpectator.assetPath = "ASSETS\\ENEMIES\\IMIGH.OBJ;1";
    imighSpectator.animAdapter.assignGenericTracks(2); // HoverIdle, WatchMocking
    layout.enemySpawns.push_back(imighSpectator);

    // Climax fight trigger coordinates
    LevelTrigger bossFightTrigger;
    bossFightTrigger.minBound.set(-15.0f, 0.0f, 105.0f, 1.0f);
    bossFightTrigger.maxBound.set(15.0f, 8.0f, 135.0f, 1.0f);
    bossFightTrigger.actionType = "TRIGGER_ARCHBISHOP_SERIS_MUTATION_FIGHT";
    bossFightTrigger.isTriggered = false;
    layout.triggers.push_back(bossFightTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene4_1_FrozenCliff() {
    LevelLayout layout;
    layout.sceneId = 41;
    layout.sceneTitle = "Scene 4.1: The Frozen Cliff Path (Exterior)";

    // Narrow cliffside ledge segments ascending the mountain
    for (int z = 0; z <= 100; z += 20) {
        LevelMeshNode cliffSeg;
        cliffSeg.name = "Kaelor_Cliff_Ledge_Seg_" + std::to_string(z);
        cliffSeg.position.set(0.0f, static_cast<float>(z) * 0.15f, static_cast<float>(z), 1.0f); // Steep ascent
        cliffSeg.scale.set(6.0f, 1.5f, 20.0f, 1.0f);
        cliffSeg.assetPath = "ASSETS\\LEVELS\\FROZEN_CLIFF.OBJ;1";
        layout.staticMeshes.push_back(cliffSeg);

        // Frozen stone gargoyles lining the cliff
        if (z % 40 == 0) {
            LevelMeshNode gargoyle;
            gargoyle.name = "Frozen_Stone_Gargoyle_Prop_" + std::to_string(z);
            gargoyle.position.set(3.5f, (static_cast<float>(z) * 0.15f) + 2.0f, static_cast<float>(z), 1.0f);
            gargoyle.scale.set(2.0f, 3.5f, 2.0f, 1.0f);
            gargoyle.assetPath = "ASSETS\\PROPS\\STONE_GARGOYLE.OBJ;1";
            gargoyle.animAdapter.assignGenericTracks(1); // Static stone
            layout.props.push_back(gargoyle);
        }
    }

    // Academy entrance through shattered stained-glass window at height Y = 15, Z = 120
    LevelMeshNode academyFacade;
    academyFacade.name = "Kaelor_Academy_Shattered_Facade";
    academyFacade.position.set(0.0f, 15.0f, 120.0f, 1.0f);
    academyFacade.scale.set(10.0f, 18.0f, 4.0f, 1.0f);
    academyFacade.assetPath = "ASSETS\\LEVELS\\SHATTERED_FACADE.OBJ;1";
    layout.staticMeshes.push_back(academyFacade);

    // Stained-glass infiltration trigger
    LevelTrigger archiveEntryTrigger;
    archiveEntryTrigger.minBound.set(-4.0f, 13.0f, 115.0f, 1.0f);
    archiveEntryTrigger.maxBound.set(4.0f, 19.0f, 125.0f, 1.0f);
    archiveEntryTrigger.actionType = "LOAD_SCENE_4_2_ARCHIVES";
    archiveEntryTrigger.isTriggered = false;
    layout.triggers.push_back(archiveEntryTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene4_2_GrandArchives() {
    LevelLayout layout;
    layout.sceneId = 42;
    layout.sceneTitle = "Scene 4.2: The Grand Archives (Interior)";

    // Repetitive library bookshelves arranged in a grid matrix creating a maze pathway
    for (int x = -15; x <= 15; x += 10) {
        for (int z = 10; z <= 130; z += 30) {
            // Leave holes in the grid to form a winding maze
            if ((x == 5 && z == 40) || (x == -5 && z == 100)) {
                continue;
            }

            LevelMeshNode bookshelf;
            bookshelf.name = "Archive_Bookshelf_Grid_" + std::to_string(x) + "_" + std::to_string(z);
            bookshelf.position.set(static_cast<float>(x), 0.0f, static_cast<float>(z), 1.0f);
            bookshelf.scale.set(4.0f, 14.0f, 12.0f, 1.0f);
            bookshelf.assetPath = "ASSETS\\LEVELS\\LIBRARY_BOOKSHELF.OBJ;1";
            layout.staticMeshes.push_back(bookshelf);

            // Add book stack details
            LevelMeshNode bookstack;
            bookstack.name = "Spilled_Books_Detail_" + std::to_string(x) + "_" + std::to_string(z);
            bookstack.position.set(static_cast<float>(x) + 1.0f, 0.5f, static_cast<float>(z) + 1.0f, 1.0f);
            bookstack.scale.set(1.5f, 1.0f, 1.5f, 1.0f);
            bookstack.assetPath = "ASSETS\\PROPS\\BOOK_STACK.OBJ;1";
            layout.props.push_back(bookstack);
        }
    }

    // Heavy brass library vault door at (0, 0, 150)
    LevelMeshNode brassVaultDoor;
    brassVaultDoor.name = "Heavy_Brass_Vault_Door";
    brassVaultDoor.position.set(0.0f, 0.0f, 150.0f, 1.0f);
    brassVaultDoor.scale.set(8.0f, 10.0f, 2.0f, 1.0f);
    brassVaultDoor.assetPath = "ASSETS\\PROPS\\BRASS_VAULT.OBJ;1";
    brassVaultDoor.animAdapter.assignGenericTracks(2); // Locked, UnlockedSliding
    layout.props.push_back(brassVaultDoor);

    // Script Phantoms spawns roaming between bookshelves rows
    LevelMeshNode phantom1;
    phantom1.name = "Script_Phantom_Acolyte_1";
    phantom1.position.set(-8.0f, 2.0f, 30.0f, 1.0f);
    phantom1.assetPath = "ASSETS\\ENEMIES\\SCRIPT_PHANTOM.OBJ;1";
    phantom1.animAdapter.assignGenericTracks(3); // HoverIdle, CastGlyph, FadeOut
    layout.enemySpawns.push_back(phantom1);

    LevelMeshNode phantom2;
    phantom2.name = "Script_Phantom_Acolyte_2";
    phantom2.position.set(8.0f, 2.0f, 80.0f, 1.0f);
    phantom2.assetPath = "ASSETS\\ENEMIES\\SCRIPT_PHANTOM.OBJ;1";
    phantom2.animAdapter.assignGenericTracks(3);
    layout.enemySpawns.push_back(phantom2);

    // Vault door unlock/transition trigger at (0, 0, 150)
    LevelTrigger vaultTrigger;
    vaultTrigger.minBound.set(-5.0f, 0.0f, 144.0f, 1.0f);
    vaultTrigger.maxBound.set(5.0f, 8.0f, 155.0f, 1.0f);
    vaultTrigger.actionType = "LOAD_SCENE_4_3_ASTROLABE";
    vaultTrigger.isTriggered = false;
    layout.triggers.push_back(vaultTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene4_3_ClockworkAstrolabe() {
    LevelLayout layout;
    layout.sceneId = 43;
    layout.sceneTitle = "Scene 4.3: The Clockwork Astrolabe (Interior/Void Platforming)";

    // Concentric rotating brass rings centered at (0, 0, 0)
    LevelMeshNode ringOuter;
    ringOuter.name = "Astrolabe_Outer_Concentric_Ring";
    ringOuter.position.set(0.0f, 0.0f, 0.0f, 1.0f);
    ringOuter.rotation.set(0.0f, 12.0f, 0.0f, 1.0f); // Rotates at speed 1.0
    ringOuter.scale.set(40.0f, 1.5f, 40.0f, 1.0f);
    ringOuter.assetPath = "ASSETS\\LEVELS\\ASTRO_RING_OUTER.OBJ;1";
    layout.staticMeshes.push_back(ringOuter);

    LevelMeshNode ringMiddle;
    ringMiddle.name = "Astrolabe_Middle_Concentric_Ring";
    ringMiddle.position.set(0.0f, 0.0f, 0.0f, 1.0f);
    ringMiddle.rotation.set(0.0f, -25.0f, 0.0f, 1.0f); // Rotates at speed -1.8
    ringMiddle.scale.set(28.0f, 1.5f, 28.0f, 1.0f);
    ringMiddle.assetPath = "ASSETS\\LEVELS\\ASTRO_RING_MID.OBJ;1";
    layout.staticMeshes.push_back(ringMiddle);

    LevelMeshNode ringInner;
    ringInner.name = "Astrolabe_Inner_Concentric_Ring";
    ringInner.position.set(0.0f, 0.0f, 0.0f, 1.0f);
    ringInner.rotation.set(0.0f, 45.0f, 0.0f, 1.0f); // Rotates at speed 2.5
    ringInner.scale.set(16.0f, 1.5f, 16.0f, 1.0f);
    ringInner.assetPath = "ASSETS\\LEVELS\\ASTRO_RING_INNER.OBJ;1";
    layout.staticMeshes.push_back(ringInner);

    // Detail props: Gear drive assemblies & alignment dials
    LevelMeshNode gearDrive;
    gearDrive.name = "Clockwork_Astrolabe_Gear_Drive";
    gearDrive.position.set(0.0f, -4.0f, 0.0f, 1.0f);
    gearDrive.scale.set(8.0f, 6.0f, 8.0f, 1.0f);
    gearDrive.assetPath = "ASSETS\\PROPS\\GEAR_DRIVE.OBJ;1";
    layout.props.push_back(gearDrive);

    // Astrolabe Alignment Trigger
    LevelTrigger alignTrigger;
    alignTrigger.minBound.set(-4.0f, -1.0f, -4.0f, 1.0f);
    alignTrigger.maxBound.set(4.0f, 4.0f, 4.0f, 1.0f);
    alignTrigger.actionType = "TRIGGER_ASTROLABE_CONSTELLATION_ALIGN";
    alignTrigger.isTriggered = false;
    layout.triggers.push_back(alignTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene5_1_PetrifiedForest() {
    LevelLayout layout;
    layout.sceneId = 51;
    layout.sceneTitle = "Scene 5.1: The Petrified Forest Entry (Exterior)";

    // Populate a wide terrain mesh with low-poly petrified trees
    // Terrain block
    LevelMeshNode terrain;
    terrain.name = "Morvain_Bloodfield_Forest_Floor";
    terrain.position.set(0.0f, -1.0f, 75.0f, 1.0f);
    terrain.scale.set(150.0f, 2.0f, 150.0f, 1.0f);
    terrain.assetPath = "ASSETS\\LEVELS\\BLOOD_FIELDS_TERRAIN.OBJ;1";
    layout.staticMeshes.push_back(terrain);

    // Scattered jagged petrified trees creating a chaotic forest maze
    for (int x = -60; x <= 60; x += 30) {
        for (int z = 10; z <= 140; z += 30) {
            // Apply slight randomness offsets by altering values depending on coordinates
            float offsetX = static_cast<float>((x * z) % 9) - 4.5f;
            float offsetZ = static_cast<float>((x + z) % 9) - 4.5f;

            LevelMeshNode petrifiedTree;
            petrifiedTree.name = "Morvain_Petrified_Tree_" + std::to_string(x) + "_" + std::to_string(z);
            petrifiedTree.position.set(static_cast<float>(x) + offsetX, 0.0f, static_cast<float>(z) + offsetZ, 1.0f);
            petrifiedTree.scale.set(3.0f, 15.0f, 3.0f, 1.0f);
            petrifiedTree.assetPath = "ASSETS\\LEVELS\\PETRIFIED_TREE.OBJ;1";
            layout.staticMeshes.push_back(petrifiedTree);
        }
    }

    // Shattered swords thrust into the crimson mud
    for (int i = 0; i < 5; ++i) {
        LevelMeshNode brokenSword;
        brokenSword.name = "Morvain_Shattered_Battlefield_Sword_" + std::to_string(i);
        brokenSword.position.set(-15.0f + static_cast<float>(i * 8), 0.5f, 40.0f + static_cast<float>(i * 12), 1.0f);
        brokenSword.rotation.set(0.0f, 0.0f, 15.0f, 1.0f); // slanted
        brokenSword.scale.set(1.0f, 2.5f, 1.0f, 1.0f);
        brokenSword.assetPath = "ASSETS\\PROPS\\BROKEN_SWORD.OBJ;1";
        layout.props.push_back(brokenSword);
    }

    // Transition trigger at the end of the forest leading to the Red Clearing (Scene 5.2)
    LevelTrigger forestExitTrigger;
    forestExitTrigger.minBound.set(-20.0f, 0.0f, 140.0f, 1.0f);
    forestExitTrigger.maxBound.set(20.0f, 8.0f, 155.0f, 1.0f);
    forestExitTrigger.actionType = "LOAD_SCENE_5_2_RED_CLEARING";
    forestExitTrigger.isTriggered = false;
    layout.triggers.push_back(forestExitTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene5_2_RedClearing() {
    LevelLayout layout;
    layout.sceneId = 52;
    layout.sceneTitle = "Scene 5.2: The Red Clearing Boss Arena (Exterior)";

    // Large circular battlefield clearing
    LevelMeshNode arenaFloor;
    arenaFloor.name = "Red_Clearing_Boss_Arena_Floor";
    arenaFloor.position.set(0.0f, -0.5f, 75.0f, 1.0f);
    arenaFloor.scale.set(120.0f, 1.0f, 120.0f, 1.0f);
    arenaFloor.assetPath = "ASSETS\\LEVELS\\RED_ARENA_FLOOR.OBJ;1";
    layout.staticMeshes.push_back(arenaFloor);

    // Circle of shattered swords enclosing the battlefield arena
    for (int i = 0; i < 12; ++i) {
        float angle = static_cast<float>(i) * 30.0f * (3.14159f / 180.0f);
        float x = cos(angle) * 35.0f;
        float z = sin(angle) * 35.0f + 75.0f; // centered at Z=75

        LevelMeshNode circleSword;
        circleSword.name = "Ritual_Shattered_Sword_Border_" + std::to_string(i);
        circleSword.position.set(x, 1.0f, z, 1.0f);
        circleSword.rotation.set(0.0f, -static_cast<float>(i) * 30.0f, 20.0f, 1.0f);
        circleSword.scale.set(1.0f, 3.0f, 1.0f, 1.0f);
        circleSword.assetPath = "ASSETS\\PROPS\\BROKEN_SWORD.OBJ;1";
        layout.props.push_back(circleSword);
    }

    // Corrupted Aevior Boss Spawn in center of clearing (0, 0, 75)
    LevelMeshNode corruptedAeviorBoss;
    corruptedAeviorBoss.name = "Corrupted_Aevior_The_Deceived_Boss";
    corruptedAeviorBoss.position.set(0.0f, 0.5f, 75.0f, 1.0f);
    corruptedAeviorBoss.scale.set(1.1f, 1.1f, 1.1f, 1.0f);
    corruptedAeviorBoss.assetPath = "ASSETS\\ENEMIES\\AEVIOR_CORRUPT.OBJ;1";
    // Idle, Walk, ErraticStrike, VowArtEruption, SacrificialBlock, Die
    corruptedAeviorBoss.animAdapter.assignGenericTracks(5);
    layout.enemySpawns.push_back(corruptedAeviorBoss);

    // Wire the Act V Boss Completion Lockout Trigger at coordinates (0, 0, 150)
    // Linked directly to meta_narrative.cpp for choice lockout & glitch intercept loop
    LevelTrigger bossArenaClimaxTrigger;
    bossArenaClimaxTrigger.minBound.set(-15.0f, 0.0f, 140.0f, 1.0f);
    bossArenaClimaxTrigger.maxBound.set(15.0f, 8.0f, 160.0f, 1.0f);
    bossArenaClimaxTrigger.actionType = "TRIGGER_ACT5_BOSS_COMPLETION_LOCKOUT_GLITCH";
    bossArenaClimaxTrigger.isTriggered = false;
    layout.triggers.push_back(bossArenaClimaxTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene6_1_MistyMarsh() {
    LevelLayout layout;
    layout.sceneId = 61;
    layout.sceneTitle = "Scene 6.1: The Misty Marsh Shore (Exterior)";

    // Water meshes along the Y-floor plane with a 40% player movement speed modifier attached to collision
    for (int x = -40; x <= 40; x += 20) {
        LevelMeshNode waterMesh;
        waterMesh.name = "Lys_Swamp_Water_Collision_SpeedFactor_0.40_" + std::to_string(x);
        waterMesh.position.set(static_cast<float>(x), -1.5f, 50.0f, 1.0f);
        waterMesh.scale.set(20.0f, 0.1f, 100.0f, 1.0f);
        waterMesh.assetPath = "ASSETS\\LEVELS\\SWAMP_WATER.OBJ;1";
        layout.staticMeshes.push_back(waterMesh);
    }

    // Moss-covered fallen tree trunk bridge (max 80 polygons)
    LevelMeshNode treeBridge;
    treeBridge.name = "Lys_Moss_Tree_Trunk_Bridge";
    treeBridge.position.set(0.0f, 0.5f, 40.0f, 1.0f);
    treeBridge.rotation.set(0.0f, 90.0f, 0.0f, 1.0f);
    treeBridge.scale.set(2.0f, 2.0f, 30.0f, 1.0f);
    treeBridge.assetPath = "ASSETS\\PROPS\\FALLEN_TREE_TRUNK.OBJ;1";
    layout.props.push_back(treeBridge);

    // Misty Marsh Shore land segments
    LevelMeshNode shoreA;
    shoreA.name = "Lys_Misty_Marsh_Shore_Land_A";
    shoreA.position.set(0.0f, 0.0f, 0.0f, 1.0f);
    shoreA.scale.set(40.0f, 1.0f, 20.0f, 1.0f);
    shoreA.assetPath = "ASSETS\\LEVELS\\MUDDY_SHORE_A.OBJ;1";
    layout.staticMeshes.push_back(shoreA);

    LevelMeshNode shoreB;
    shoreB.name = "Lys_Misty_Marsh_Shore_Land_B";
    shoreB.position.set(0.0f, 0.0f, 100.0f, 1.0f);
    shoreB.scale.set(40.0f, 1.0f, 20.0f, 1.0f);
    shoreB.assetPath = "ASSETS\\LEVELS\\MUDDY_SHORE_B.OBJ;1";
    layout.staticMeshes.push_back(shoreB);

    // "Mire Drowned" entities surge out of the water instantly
    for (int i = 0; i < 3; ++i) {
        LevelMeshNode mireDrowned;
        mireDrowned.name = "Mire_Drowned_Husk_Spawn_" + std::to_string(i);
        mireDrowned.position.set(-15.0f + static_cast<float>(i * 15), -1.2f, 35.0f + static_cast<float>(i * 20), 1.0f);
        mireDrowned.assetPath = "ASSETS\\ENEMIES\\MIRE_DROWNED.OBJ;1";
        mireDrowned.animAdapter.assignGenericTracks(3); // IdleWater, SurgeOut, SlashAttack
        layout.enemySpawns.push_back(mireDrowned);
    }

    // Transition Trigger to Sunken Baptistry at Z=100
    LevelTrigger baptistryTrigger;
    baptistryTrigger.minBound.set(-10.0f, -1.0f, 95.0f, 1.0f);
    baptistryTrigger.maxBound.set(10.0f, 5.0f, 105.0f, 1.0f);
    baptistryTrigger.actionType = "LOAD_SCENE_6_4_SUNKEN_BAPTISTRY";
    baptistryTrigger.isTriggered = false;
    layout.triggers.push_back(baptistryTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene6_4_SunkenBaptistry() {
    LevelLayout layout;
    layout.sceneId = 64;
    layout.sceneTitle = "Scene 6.4: The Sunken Baptistry (Interior)";

    // Sinking Ruin Steps & Half-submerged limestone archway
    LevelMeshNode archway;
    archway.name = "Lys_Half_Submerged_Limestone_Archway";
    archway.position.set(0.0f, 0.0f, 150.0f, 1.0f);
    archway.scale.set(12.0f, 15.0f, 4.0f, 1.0f);
    archway.assetPath = "ASSETS\\LEVELS\\SUBMERGED_ARCHWAY.OBJ;1";
    layout.staticMeshes.push_back(archway);

    for (int i = 0; i < 5; ++i) {
        LevelMeshNode step;
        step.name = "Lys_Sinking_Ruin_Steps_" + std::to_string(i);
        step.position.set(0.0f, -2.0f + static_cast<float>(i) * 0.5f, 160.0f + static_cast<float>(i) * 3.0f, 1.0f);
        step.scale.set(10.0f, 1.0f, 4.0f, 1.0f);
        step.assetPath = "ASSETS\\LEVELS\\SINKING_STEPS.OBJ;1";
        layout.staticMeshes.push_back(step);
    }

    // Glowing turquoise swamp water
    LevelMeshNode glowingWater;
    glowingWater.name = "Lys_Bioluminescent_Turquoise_Water_Collision_SpeedFactor_0.40";
    glowingWater.position.set(0.0f, -4.0f, 200.0f, 1.0f);
    glowingWater.scale.set(80.0f, 0.1f, 80.0f, 1.0f);
    glowingWater.assetPath = "ASSETS\\LEVELS\\GLOWING_WATER.OBJ;1";
    layout.staticMeshes.push_back(glowingWater);

    // Witch of the Mire boss at coordinates (0, -5, 220)
    LevelMeshNode witchBoss;
    witchBoss.name = "Lys_Witch_of_the_Mire_Boss";
    witchBoss.position.set(0.0f, -5.0f, 220.0f, 1.0f);
    witchBoss.scale.set(1.2f, 1.2f, 1.2f, 1.0f);
    witchBoss.assetPath = "ASSETS\\ENEMIES\\WITCH_OF_MIRE.OBJ;1";
    // Idle, HoverStaff, CastToxicWave, SummonDrowned, Die
    witchBoss.animAdapter.assignGenericTracks(5);
    layout.enemySpawns.push_back(witchBoss);

    // Exit trigger to Foundries of Ardent
    LevelTrigger foundryExitTrigger;
    foundryExitTrigger.minBound.set(-8.0f, -5.0f, 235.0f, 1.0f);
    foundryExitTrigger.maxBound.set(8.0f, 5.0f, 245.0f, 1.0f);
    foundryExitTrigger.actionType = "LOAD_SCENE_7_2_ASSEMBLY_BELTS";
    foundryExitTrigger.isTriggered = false;
    layout.triggers.push_back(foundryExitTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene7_2_AssemblyBelts() {
    LevelLayout layout;
    layout.sceneId = 72;
    layout.sceneTitle = "Scene 7.2: The Assembly Belts (Interior)";

    // Conveyor belt platform meshes with continuous velocity vector transformation
    for (int z = 10; z <= 130; z += 40) {
        LevelMeshNode conveyorBelt;
        conveyorBelt.name = "Ardent_Conveyor_Belt_Velocity_X_0.0_Z_4.5_" + std::to_string(z);
        conveyorBelt.position.set(0.0f, 2.0f, static_cast<float>(z), 1.0f);
        conveyorBelt.scale.set(8.0f, 1.5f, 30.0f, 1.0f);
        conveyorBelt.assetPath = "ASSETS\\LEVELS\\CONVEYOR_BELT.OBJ;1";
        layout.staticMeshes.push_back(conveyorBelt);

        // Massive mechanical industrial gears (max 60 polygons)
        LevelMeshNode gear;
        gear.name = "Ardent_Industrial_Gear_Prop_" + std::to_string(z);
        gear.position.set(-6.0f, 3.5f, static_cast<float>(z) + 10.0f, 1.0f);
        gear.rotation.set(90.0f, 0.0f, 0.0f, 1.0f);
        gear.scale.set(4.0f, 4.0f, 1.0f, 1.0f);
        gear.assetPath = "ASSETS\\PROPS\\INDUSTRIAL_GEAR.OBJ;1";
        layout.props.push_back(gear);
    }

    // Piston hazard platform
    LevelMeshNode piston;
    piston.name = "Ardent_Crushing_Piston_Hazard";
    piston.position.set(0.0f, 12.0f, 150.0f, 1.0f);
    piston.scale.set(5.0f, 10.0f, 5.0f, 1.0f);
    piston.assetPath = "ASSETS\\PROPS\\CRUSHING_PISTON.OBJ;1";
    piston.animAdapter.assignGenericTracks(2); // Up, StrikeDown
    layout.props.push_back(piston);

    // Vow-Forged Golems spawns patrolling the belts (max 850 polygons)
    LevelMeshNode golem1;
    golem1.name = "Vow_Forged_Golem_Sentinel_1";
    golem1.position.set(0.0f, 3.0f, 40.0f, 1.0f);
    golem1.scale.set(1.4f, 1.4f, 1.4f, 1.0f);
    golem1.assetPath = "ASSETS\\ENEMIES\\VOW_FORGED_GOLEM.OBJ;1";
    golem1.animAdapter.assignGenericTracks(3); // WalkPatrol, HeavyStrike, OverheatErupt
    layout.enemySpawns.push_back(golem1);

    LevelMeshNode golem2;
    golem2.name = "Vow_Forged_Golem_Sentinel_2";
    golem2.position.set(0.0f, 3.0f, 100.0f, 1.0f);
    golem2.scale.set(1.4f, 1.4f, 1.4f, 1.0f);
    golem2.assetPath = "ASSETS\\ENEMIES\\VOW_FORGED_GOLEM.OBJ;1";
    golem2.animAdapter.assignGenericTracks(3);
    layout.enemySpawns.push_back(golem2);

    // Transition trigger to Smelting Core Cathedral
    LevelTrigger coreTrigger;
    coreTrigger.minBound.set(-6.0f, 1.0f, 170.0f, 1.0f);
    coreTrigger.maxBound.set(6.0f, 8.0f, 185.0f, 1.0f);
    coreTrigger.actionType = "LOAD_SCENE_7_3_SMELTING_CORE";
    coreTrigger.isTriggered = false;
    layout.triggers.push_back(coreTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene7_3_SmeltingCore() {
    LevelLayout layout;
    layout.sceneId = 73;
    layout.sceneTitle = "Scene 7.3: The Smelting Core Cathedral (Interior Climax)";

    // Smelting Core Cathedral Arena at (0, 10, 400)
    LevelMeshNode coreArena;
    coreArena.name = "Ardent_Smelting_Core_Cathedral_Arena";
    coreArena.position.set(0.0f, 10.0f, 400.0f, 1.0f);
    coreArena.scale.set(100.0f, 2.0f, 100.0f, 1.0f);
    coreArena.assetPath = "ASSETS\\LEVELS\\SMELTING_CORE_CATHEDRAL.OBJ;1";
    layout.staticMeshes.push_back(coreArena);

    // Molten lava conduits running along the perimeter of the arena
    for (int i = 0; i < 4; ++i) {
        float offsetZ = -40.0f + static_cast<float>(i * 25.0f);
        LevelMeshNode lavaConduit;
        lavaConduit.name = "Ardent_Molten_Lava_Conduit_Scrolling_" + std::to_string(i);
        lavaConduit.position.set(-35.0f, 9.5f, 400.0f + offsetZ, 1.0f);
        lavaConduit.scale.set(10.0f, 0.5f, 20.0f, 1.0f);
        lavaConduit.assetPath = "ASSETS\\LEVELS\\MOLTEN_CONDUIT.OBJ;1";
        layout.staticMeshes.push_back(lavaConduit);
    }

    // Grand Marshal Vane boss spawn hooked to the center point (0, 10, 400)
    LevelMeshNode vaneBoss;
    vaneBoss.name = "Grand_Marshal_Vane_The_Volcanic_Warlord_Boss";
    vaneBoss.position.set(0.0f, 10.0f, 400.0f, 1.0f);
    vaneBoss.scale.set(1.3f, 1.3f, 1.3f, 1.0f);
    vaneBoss.assetPath = "ASSETS\\ENEMIES\\MARSHAL_VANE.OBJ;1";
    // Volcanic warhammer attacks and slower un-staggerable animations
    // Idle, WarhammerWalk, VolcanicStrike, MoltenSlam, Die
    vaneBoss.animAdapter.assignGenericTracks(5);
    layout.enemySpawns.push_back(vaneBoss);

    // Final Climax Lockout/Resolution Trigger
    LevelTrigger climaxTrigger;
    climaxTrigger.minBound.set(-10.0f, 9.0f, 430.0f, 1.0f);
    climaxTrigger.maxBound.set(10.0f, 18.0f, 450.0f, 1.0f);
    climaxTrigger.actionType = "TRIGGER_CLIMAX_CHURCH_DEFEATED_LOCKOUT";
    climaxTrigger.isTriggered = false;
    layout.triggers.push_back(climaxTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene8_1_CelestialCitadel() {
    LevelLayout layout;
    layout.sceneId = 81;
    layout.sceneTitle = "Scene 8.1: The Celestial Citadel (Exterior Sky Platforms)";

    // Arrange floating island meshes across an ascending vector sequence from Z=100 to Z=500
    for (int z = 100; z <= 500; z += 100) {
        float y = static_cast<float>(z - 100) * 0.1125f; // at z=500, y=45.0f

        LevelMeshNode platform;
        platform.name = "Celestial_Citadel_Floating_Platform_Node_" + std::to_string(z);
        platform.position.set(0.0f, y, static_cast<float>(z), 1.0f);
        platform.scale.set(15.0f, 2.0f, 25.0f, 1.0f);
        platform.assetPath = "ASSETS\\LEVELS\\CELESTIAL_PLATFORM.OBJ;1";
        layout.staticMeshes.push_back(platform);

        // Add some architectural debris on the floating platforms
        LevelMeshNode ruins;
        ruins.name = "Citadel_Pristine_Column_Ruins_" + std::to_string(z);
        ruins.position.set(5.0f, y + 1.0f, static_cast<float>(z) + 5.0f, 1.0f);
        ruins.scale.set(1.5f, 6.0f, 1.5f, 1.0f);
        ruins.assetPath = "ASSETS\\PROPS\\MARBLE_COLUMN.OBJ;1";
        layout.props.push_back(ruins);
    }

    // Attach instant-death volume triggers to the Y=-50 plane beneath the platforms to handle fall hazards
    LevelTrigger fallDeathTrigger;
    fallDeathTrigger.minBound.set(-200.0f, -55.0f, 0.0f, 1.0f);
    fallDeathTrigger.maxBound.set(200.0f, -45.0f, 600.0f, 1.0f);
    fallDeathTrigger.actionType = "TRIGGER_INSTANT_DEATH_FALL_HAZARD";
    fallDeathTrigger.isTriggered = false;
    layout.triggers.push_back(fallDeathTrigger);

    // Seraphim Justiciars: Elite, faceless knights with massive, low-poly golden wings
    LevelMeshNode justiciar1;
    justiciar1.name = "Seraphim_Justiciar_Sentinel_1";
    justiciar1.position.set(0.0f, 12.0f, 200.0f, 1.0f);
    justiciar1.scale.set(1.1f, 1.1f, 1.1f, 1.0f);
    justiciar1.assetPath = "ASSETS\\ENEMIES\\SERAPH_JUSTICIAR.OBJ;1";
    // HoverPatrol, WingDash, DivineSlash, Die
    justiciar1.animAdapter.assignGenericTracks(4);
    layout.enemySpawns.push_back(justiciar1);

    LevelMeshNode justiciar2;
    justiciar2.name = "Seraphim_Justiciar_Sentinel_2";
    justiciar2.position.set(0.0f, 34.5f, 400.0f, 1.0f);
    justiciar2.scale.set(1.1f, 1.1f, 1.1f, 1.0f);
    justiciar2.assetPath = "ASSETS\\ENEMIES\\SERAPH_JUSTICIAR.OBJ;1";
    justiciar2.animAdapter.assignGenericTracks(4);
    layout.enemySpawns.push_back(justiciar2);

    // The Golden Gates at the end of the sky path
    LevelMeshNode goldenGates;
    goldenGates.name = "Celestial_Citadel_Grand_Golden_Gates";
    goldenGates.position.set(0.0f, 45.0f, 500.0f, 1.0f);
    goldenGates.scale.set(10.0f, 15.0f, 2.0f, 1.0f);
    goldenGates.assetPath = "ASSETS\\PROPS\\GOLDEN_GATES.OBJ;1";
    layout.props.push_back(goldenGates);

    // Infiltration trigger leading to Malakar's Star-Chamber Nave
    LevelTrigger starChamberTrigger;
    starChamberTrigger.minBound.set(-5.0f, 44.0f, 495.0f, 1.0f);
    starChamberTrigger.maxBound.set(5.0f, 52.0f, 505.0f, 1.0f);
    starChamberTrigger.actionType = "LOAD_SCENE_8_3_STAR_CHAMBER";
    starChamberTrigger.isTriggered = false;
    layout.triggers.push_back(starChamberTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene8_3_StarChamber() {
    LevelLayout layout;
    layout.sceneId = 83;
    layout.sceneTitle = "Scene 8.3: The Star-Chamber Nave (Interior Malakar Arena)";

    // High Inquisitor Malakar's arena at (0, 45, 500)
    LevelMeshNode malakarArena;
    malakarArena.name = "Celestial_Star_Chamber_Grand_Arena";
    malakarArena.position.set(0.0f, 45.0f, 500.0f, 1.0f);
    malakarArena.scale.set(80.0f, 2.0f, 80.0f, 1.0f);
    malakarArena.assetPath = "ASSETS\\LEVELS\\STAR_CHAMBER_NAVE.OBJ;1";
    layout.staticMeshes.push_back(malakarArena);

    // Decorative floating planetary astrolabes detailing the star-chamber
    for (int i = 0; i < 4; ++i) {
        float angle = static_cast<float>(i) * 90.0f * (3.14159f / 180.0f);
        float x = cos(angle) * 25.0f;
        float z = sin(angle) * 25.0f + 500.0f;

        LevelMeshNode celestialGlobe;
        celestialGlobe.name = "Chamber_Astral_Globe_Detail_" + std::to_string(i);
        celestialGlobe.position.set(x, 48.0f, z, 1.0f);
        celestialGlobe.scale.set(3.0f, 3.0f, 3.0f, 1.0f);
        celestialGlobe.assetPath = "ASSETS\\PROPS\\ASTRAL_GLOBE.OBJ;1";
        layout.props.push_back(celestialGlobe);
    }

    // High Inquisitor Malakar boss spawn centered in the arena
    LevelMeshNode malakarBoss;
    malakarBoss.name = "High_Inquisitor_Malakar_The_Ascended_Boss";
    malakarBoss.position.set(0.0f, 46.5f, 500.0f, 1.0f);
    malakarBoss.scale.set(1.2f, 1.2f, 1.2f, 1.0f);
    malakarBoss.assetPath = "ASSETS\\ENEMIES\\MALAKAR_BOSS.OBJ;1";
    // Idle, LevitateMove, DivineLightOrb, JudgmentSmite, Die
    malakarBoss.animAdapter.assignGenericTracks(5);
    layout.enemySpawns.push_back(malakarBoss);

    // Transition trigger leading to the Infinite Mirror Core (Scene 9.1)
    LevelTrigger corePortalTrigger;
    corePortalTrigger.minBound.set(-6.0f, 45.0f, 530.0f, 1.0f);
    corePortalTrigger.maxBound.set(6.0f, 51.0f, 545.0f, 1.0f);
    corePortalTrigger.actionType = "LOAD_SCENE_9_1_INFINITE_MIRROR";
    corePortalTrigger.isTriggered = false;
    layout.triggers.push_back(corePortalTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene9_1_InfiniteMirror() {
    LevelLayout layout;
    layout.sceneId = 91;
    layout.sceneTitle = "Scene 9.1: The Infinite Mirror Plane (Surreal Core Entrance)";

    // Flat, reflective mirror floor plane using an unlit shader flag
    LevelMeshNode mirrorFloor;
    mirrorFloor.name = "Infinite_Core_Reflective_Mirror_Floor_Unlit_Shader";
    mirrorFloor.position.set(0.0f, -0.1f, 100.0f, 1.0f);
    mirrorFloor.scale.set(300.0f, 0.2f, 300.0f, 1.0f);
    mirrorFloor.assetPath = "ASSETS\\LEVELS\\MIRROR_FLOOR.OBJ;1";
    layout.staticMeshes.push_back(mirrorFloor);

    // Floating glass tile walkway leading from Z=20 to Z=150
    for (int z = 20; z <= 140; z += 15) {
        LevelMeshNode glassTile;
        glassTile.name = "Core_Floating_Glass_Pathway_Tile_" + std::to_string(z);
        glassTile.position.set(0.0f, 0.0f, static_cast<float>(z), 1.0f);
        glassTile.scale.set(6.0f, 0.5f, 12.0f, 1.0f);
        glassTile.assetPath = "ASSETS\\LEVELS\\GLASS_TILE.OBJ;1";
        layout.staticMeshes.push_back(glassTile);
    }

    // Portal trigger at Z = 150 leading to the True Altar
    LevelTrigger altarPortalTrigger;
    altarPortalTrigger.minBound.set(-4.0f, 0.0f, 140.0f, 1.0f);
    altarPortalTrigger.maxBound.set(4.0f, 4.0f, 155.0f, 1.0f);
    altarPortalTrigger.actionType = "LOAD_SCENE_9_2_TRUE_ALTAR";
    altarPortalTrigger.isTriggered = false;
    layout.triggers.push_back(altarPortalTrigger);

    return layout;
}

LevelLayout LevelBuilder::buildScene9_2_TrueAltar() {
    LevelLayout layout;
    layout.sceneId = 92;
    layout.sceneTitle = "Scene 9.2: The True Altar of the Seventh Vow (The Core Climax)";

    // Flat floor plane
    LevelMeshNode coreArenaFloor;
    coreArenaFloor.name = "Climax_True_Altar_Mirror_Floor";
    coreArenaFloor.position.set(0.0f, -0.1f, 200.0f, 1.0f);
    coreArenaFloor.scale.set(150.0f, 0.2f, 150.0f, 1.0f);
    coreArenaFloor.assetPath = "ASSETS\\LEVELS\\MIRROR_FLOOR.OBJ;1";
    layout.staticMeshes.push_back(coreArenaFloor);

    // Center the massive Oath-Binder boss entity at coordinates (0, 0, 200)
    LevelMeshNode oathBinderBoss;
    oathBinderBoss.name = "The_Oath_Binder_Climax_Boss_Entity";
    oathBinderBoss.position.set(0.0f, 0.0f, 200.0f, 1.0f);
    oathBinderBoss.scale.set(2.5f, 2.5f, 2.5f, 1.0f); // Massive entity
    oathBinderBoss.assetPath = "ASSETS\\ENEMIES\\OATH_BINDER.OBJ;1";
    // Idle, RaiseHands, ManifestFallenEchoes, HexBarrage, ShatterVows, Die
    oathBinderBoss.animAdapter.assignGenericTracks(6);
    layout.enemySpawns.push_back(oathBinderBoss);

    // Configure the interaction trigger at the Oath-Binder's death node (coordinates 0, 0, 200)
    // Executes the final engine override sequence inside meta_narrative.cpp
    LevelTrigger ultimateClimaxTrigger;
    ultimateClimaxTrigger.minBound.set(-10.0f, -2.0f, 190.0f, 1.0f);
    ultimateClimaxTrigger.maxBound.set(10.0f, 10.0f, 210.0f, 1.0f);
    ultimateClimaxTrigger.actionType = "TRIGGER_FINAL_VOW_SHATTER_OVERRIDE_GLITCH";
    ultimateClimaxTrigger.isTriggered = false;
    layout.triggers.push_back(ultimateClimaxTrigger);

    return layout;
}

void LevelBuilder::logLevelDiagnostics(const LevelLayout& layout) const {
    TYRA_LOG("=====================================================================");
    TYRA_LOG(" [LEVEL BUILDER] Assembling: %s", layout.sceneTitle.c_str());
    TYRA_LOG("=====================================================================");
    TYRA_LOG(" -> Static Geometry Nodes Stitching Count: %d meshes", static_cast<int>(layout.staticMeshes.size()));
    for (const auto& node : layout.staticMeshes) {
        TYRA_LOG("   * Static [%s] at (%.1f, %.1f, %.1f) scale (%.1f, %.1f, %.1f) bound to '%s'",
                 node.name.c_str(), node.position.x, node.position.y, node.position.z,
                 node.scale.x, node.scale.y, node.scale.z, node.assetPath.c_str());
    }

    TYRA_LOG(" -> Detail Props/Breakables Placements: %d props", static_cast<int>(layout.props.size()));
    for (const auto& prop : layout.props) {
        TYRA_LOG("   * Prop [%s] positioned at (%.1f, %.1f, %.1f)",
                 prop.name.c_str(), prop.position.x, prop.position.y, prop.position.z);
    }

    TYRA_LOG(" -> Encounter Entities Spawning Allocator: %d units", static_cast<int>(layout.enemySpawns.size()));
    for (const auto& enemy : layout.enemySpawns) {
        TYRA_LOG("   * Enemy [%s] loaded at spawn node (%.1f, %.1f, %.1f) - Animation Maps: [0:%d, 1:%d, 2:%d, 3:%d]",
                 enemy.name.c_str(), enemy.position.x, enemy.position.y, enemy.position.z,
                 enemy.animAdapter.animationIndexMap[0],
                 enemy.animAdapter.animationIndexMap[1],
                 enemy.animAdapter.animationIndexMap[2],
                 enemy.animAdapter.animationIndexMap[3]);
    }

    TYRA_LOG(" -> Active Navigation Triggers Set: %d boundaries", static_cast<int>(layout.triggers.size()));
    for (const auto& trigger : layout.triggers) {
        TYRA_LOG("   * Trigger Bounds: Min (%.1f, %.1f, %.1f) Max (%.1f, %.1f, %.1f) triggers on '%s'",
                 trigger.minBound.x, trigger.minBound.y, trigger.minBound.z,
                 trigger.maxBound.x, trigger.maxBound.y, trigger.maxBound.z,
                 trigger.actionType.c_str());
    }
    TYRA_LOG("=====================================================================");
}

} // namespace TheSeventhVow
