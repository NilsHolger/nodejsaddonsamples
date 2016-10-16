{
    "targets" : [
        {
            "target_name" : "addon",
            "sources" : ["addon.cpp", "lodepng.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}