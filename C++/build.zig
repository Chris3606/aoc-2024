const std = @import("std");

fn collect_c_sources(directory: []const u8, b: *std.Build) ![][]const u8 {
    var sources = std.ArrayList([]const u8).init(b.allocator);

    var dir = try std.fs.cwd().openDir(directory, .{ .iterate = true });

    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    const allowed_exts = [_][]const u8{ ".c", ".cpp" };

    while (try walker.next()) |entry| {
        const ext = std.fs.path.extension(entry.basename);
        const include_file = for (allowed_exts) |e| {
            if (std.mem.eql(u8, ext, e))
                break true;
        } else false;

        if (include_file) {
            const path = try std.fs.path.joinZ(b.allocator, &[_][]const u8{ directory, entry.path });
            try sources.append(path);
        }
    }

    return try sources.toOwnedSlice();
}

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Add executable target for running days
    const exe = b.addExecutable(.{
        .name = "aoc",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(.{
        .files = try collect_c_sources("src", b),
        .flags = &[_][]const u8{ "-Wall", "-Wextra", "-Wpedantic", "-Werror" },
    });
    exe.linkLibCpp();
    exe.addIncludePath(b.path("include/"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
