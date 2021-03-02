// void testBoostOptions(po::variables_map vm)
// {

//   // Files I/O section
//   if(vm.count("output"))
//     cout << "output: " << vm["output"].as<string>() << endl;
//   else
//     cout << "No output option supplied. Default value: " << vm["output"].as<string>() << endl;

//   if(vm.count("input"))
//     cout << "input: " << vm["input"].as<string>() << endl;
//   else
//     cout << "No input option supplied. Default value: "  << vm["input"].as<string>() << endl;

//   // Print section
//   if(vm.count("hiderare"))
//     cout << "hiderare: " << vm["hiderare"].as<bool>() << endl;
//   else
//     cout << "No hiderare option supplied. Default value: " << vm["hiderare"].as<string>() << endl;

//   if(vm.count("quiet"))
//     cout << "quiet: " << vm["quiet"].as<bool>() << endl;
//   else
//     cout << "No quiet option supplied. Default value: " << vm["quiet"].as<string>() << endl;


//   // Mask struct section
//   if(vm.count("minlength"))
//     cout << "minlength: " << vm["minlength"].as<unsigned int>() << endl;
//   else
//     cout << "No minlength option supplied. Default value: " << vm["minlength"].as<string>() << endl;

//   if(vm.count("maxlength"))
//     cout << "maxlength: " << vm["maxlength"].as<int>() << endl;
//   else
//     cout << "No maxlength option supplied. Default value: " << vm["maxlength"].as<string>() << endl;
// }