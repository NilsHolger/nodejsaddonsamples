{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["streaming.cpp"],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")", 
                "<!(node -e \"require('streaming-worker-sdk')\")"
]
        }
    ]
}