use std::env;
use std::path::PathBuf;

fn main() {
    let target = env::var("TARGET").unwrap();

    let lib_dir = if target.contains("i686") {
        "includes/sdk/libs/TwinCAT RT (x86)"
    } else {
        "includes/sdk/libs/TwinCAT RT (x64)"
    };

    println!("cargo:rustc-link-search=native={}", lib_dir);
    println!("cargo:rustc-link-lib=dylib=TcAdsDll");

    println!("cargo:rerun-if-changed=wrapper_sdk.h");

    let bindings = bindgen::Builder::default()
        .header("wrapper_sdk.h")
        .clang_arg("--include-directory=includes/sdk/headers")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .generate()
        .unwrap();

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap()).join("bindings.rs");

    bindings.write_to_file(&out_path).unwrap();
}
