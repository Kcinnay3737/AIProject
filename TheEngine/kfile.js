const path = require('path');
const fs = require('fs');
let project = new Project('TheEngine');

project.addProvider = function(proj, isRoot=false){
    proj.addIncludeDir("C:/Program Files (x86)/Visual Leak Detector/include");
    proj.addIncludeDir("C:/Program Files (x86)/Visual Leak Detector/include");
    proj.addLib("C:/Program Files (x86)/Visual Leak Detector/lib/Win64/vld");
    const sdl2 = true;//process.argv.indexOf("--sdl2") >= 0;
    if(sdl2){
        fs.copyFileSync("./SDL/lib/SDL2.dll", "./Deployment/SDL2.dll");
        fs.copyFileSync("./SDL/lib/SDL2_image.dll", "./Deployment/SDL2_image.dll");
        fs.copyFileSync("./SDL/lib/SDL2_ttf.dll", "./Deployment/SDL2_ttf.dll");
        fs.copyFileSync("./SDL/lib/SDL2_mixer.dll", "./Deployment/SDL2_mixer.dll");
        if(!isRoot){
            proj.addDefine("USE_SDL");
            proj.addIncludeDir(path.resolve("./SDL/include"));
        }
        proj.addLib("./SDL/lib/SDL2");
        proj.addLib("./SDL/lib/SDL2main");
        proj.addLib("./SDL/lib/SDL2_image");
        proj.addLib("./SDL/lib/SDL2_ttf");
        proj.addLib("./SDL/lib/SDL2_mixer");
    }
};
project.kore = false;
project.setCppStd("C++20");

project.addDefine("KINC_STATIC_COMPILE");
project.isStaticLib = true;

project.addIncludeDir(path.resolve("./TheEngine/Includes"));
project.addIncludeDir(path.resolve("./External/eigen"));
project.addIncludeDir(path.resolve("./External/Boost"));
project.addIncludeDir(path.resolve("./External/AI-Toolbox/include"));

project.addFiles(
    'Sources/**',
    'Includes/**',
    //path.resolve("./External/AI-Toolbox/src/Bandit/**"),
    //path.resolve("./External/AI-Toolbox/src/Factored/**"),
    path.resolve("./External/AI-Toolbox/src/MDP/**"),
    path.resolve("./External/AI-Toolbox/src/Utils/**"),
    path.resolve("./External/AI-Toolbox/src/Seeder/**")
);

project.addProvider(project,false);

resolve(project);