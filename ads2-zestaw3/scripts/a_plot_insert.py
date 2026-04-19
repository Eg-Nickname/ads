import pandas as pd
import matplotlib.pyplot as plt

colors = [
    "#8a3ffc",
    "#3ddbd9",
    "#005d5d",
    "#007d79",
    "#6929c4",
    "#08bdba",
    "#a56eff",
]


def save_plot(csv_file="set_pq_benchmarks.csv"):
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

    on_cols = ["Insert_Avg_ms", "Remove_ms"]

    for idx, col in enumerate(on_cols):
        plt.plot(
            df["N"],
            df[col],
            marker="o",
            label=col.replace("_ms", ""),
            color=colors[idx],
        )

    # plt.yscale("log")

    plt.title("PQ Operations")
    plt.xlabel("PQ Size (N)")
    plt.ylabel("Execution Time (micros)")
    plt.legend(loc="upper left")
    plt.grid(True, linestyle="--", alpha=0.6)

    plt.tight_layout()
    plt.savefig("set_pq_n.png", dpi=300)


if __name__ == "__main__":
    save_plot()
