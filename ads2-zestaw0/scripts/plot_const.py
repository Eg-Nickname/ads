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


def save_constant_plot(csv_file="../build/set_benchmarks.csv"):
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

    o1_cols = ["Insert_ns", "Remove_ns", "Contains_ns", "Size_ns"]

    for idx, col in enumerate(o1_cols):
        plt.plot(
            df["N"],
            df[col],
            marker="x",
            label=col.replace("_ns", ""),
            color=colors[idx],
        )

    plt.title("Element Operations $O(1)$")
    plt.xlabel("Set Size (N)")
    plt.ylabel("Execution Time (ns)")

    curr_ymin, curr_ymax = plt.ylim()
    plt.ylim(0, curr_ymax * 1.2)

    plt.legend(loc="upper right")
    plt.grid(True, linestyle="--", alpha=0.6)

    plt.tight_layout()
    plt.savefig("element_operations_constant.png", dpi=300)
    print("Constant plot saved as: element_operations_constant.png")


if __name__ == "__main__":
    save_constant_plot()
