import pandas as pd
import matplotlib.pyplot as plt

colors = [
    "#005d5d",
    "#007d79",
    "#6929c4",
    "#08bdba",
    "#3ddbd9",
    "#8a3ffc",
    "#a56eff",
]


def save_linear_plot(csv_file="../build/set_benchmarks.csv"):
    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print("CSV not found.")
        return

    plt.figure(figsize=(10, 6))
    ax = plt.gca()
    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)
    plt.grid(True, linestyle="--", linewidth=0.5)

    on_cols = ["Union_ms", "Intersect_ms", "Subtract_ms", "SymDiff_ms", "IsSubset_ms"]

    for idx, col in enumerate(on_cols):
        plt.plot(
            df["N"],
            df[col],
            marker="o",
            label=col.replace("_ms", ""),
            color=colors[idx],
        )

    plt.title("Set Operations $O(N)$")
    plt.xlabel("Set Size (N)")
    plt.ylabel("Execution Time (ms)")
    plt.legend(loc="upper left")
    plt.grid(True, linestyle="--", alpha=0.6)

    plt.tight_layout()
    plt.savefig("set_operations_linear.png", dpi=300)
    print("Linear plot saved as: set_operations_linear.png")


if __name__ == "__main__":
    save_linear_plot()
