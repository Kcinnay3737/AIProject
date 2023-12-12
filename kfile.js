let project = new Project("BOI");

project.kore = false;

project.addFiles(
    "BOI/**",
);

project.setDebugDir("Deployment");

project.addIncludeDir("./TheEngine/Includes");
project.addIncludeDir("./BOI/Includes");

project.setCppStd("C++20");

project.flatten();

const otherproj = await project.addProject("TheEngine");
otherproj.addProvider(project, true);

resolve(project);